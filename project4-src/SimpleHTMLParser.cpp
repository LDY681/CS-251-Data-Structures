#include <iostream>
#include "SimpleHTMLParser.h"
using namespace std;

// Init and de-init global curl context
class CurlSt {
public:
	CurlSt() {
		CURLcode ret = curl_global_init(CURL_GLOBAL_ALL);
		if (ret != CURLE_OK) {
			cerr << "Failed to initialize libcurl!" << endl;
			exit(-1);
	}}
	~CurlSt() { curl_global_cleanup(); }
};
// Static global object - constructs before main() and destructs
// after main() returns.
static CurlSt curlSt;


// Initialize a libcurl context to handle network transfers
SimpleHTMLParser::SimpleHTMLParser() :
		curlh(NULL),
		curlErr(CURL_ERROR_SIZE, '\0') {
	// Create the context
	curlh = curl_easy_init();
	if (!curlh) {
		error = "Failed to create libcurl context!";
		return;
	}

	// Set the callback function
	typedef size_t(*curl_cb)(void*,size_t,size_t,void*);
	curl_easy_setopt(curlh, CURLOPT_WRITEFUNCTION, (curl_cb)
		[](void* buf, size_t sz, size_t nb, void* data) -> size_t {
			// Copy the buffer into the html string
			string* html = (string*)data;
			html->append((const char*)buf, sz * nb);
			return sz * nb;
		});
	// Set the write buffer to the html string
	curl_easy_setopt(curlh, CURLOPT_WRITEDATA, &html);
	// Some sites expect a user-agent
	curl_easy_setopt(curlh, CURLOPT_USERAGENT, "libcurl-agent/1.0");
	// Only allow HTTP or HTTPS
	curl_easy_setopt(curlh, CURLOPT_PROTOCOLS,
		CURLPROTO_HTTP | CURLPROTO_HTTPS);
	// Set buffer for errors
	curl_easy_setopt(curlh, CURLOPT_ERRORBUFFER, (char*)curlErr.data());
}
// Release libcurl context
SimpleHTMLParser::~SimpleHTMLParser() {
	if (curlh) { curl_easy_cleanup(curlh); curlh = NULL; }
}

// Downloads and parses an HTML file at the given URL. On success, returns
// true and populates internal strings with the HTML content. If an error
// occurs, returns false.
bool SimpleHTMLParser::parse(string url) {
	if (!curlh) return false;

	// Clear the existing content
	html.clear();
	text.clear();
	urls.clear();

	try {
		// Download the HTML file
		fetchHTML(url);
		// Parse the HTML file to remove tags and separate urls
		parseHTML();

	// Handle any errors
	} catch (const exception& e) {
		error = e.what();
		return false;
	}

	return true;
}

// Downloads the HTML file at the given URL. On success, fills the
// internal data member string html with the raw HTML content. If an
// error occurs, an exception is thrown.
void SimpleHTMLParser::fetchHTML(string url) {
	// Set the URL to fetch
	curl_easy_setopt(curlh, CURLOPT_URL, url.c_str());

	// Perform the transfer
	CURLcode ret = curl_easy_perform(curlh);
	if (ret != CURLE_OK)
		throw runtime_error(curlErr);

	// Get the content type
	char* ct;
	ret = curl_easy_getinfo(curlh, CURLINFO_CONTENT_TYPE, &ct);
	if (ret != CURLE_OK)
		throw runtime_error(curlErr);

	// Make sure it's an HTML file
	if (!ct)
		throw runtime_error("No content type");
	string contentType(ct);
	string HTMLTag("text/html");
	if (contentType.compare(0, HTMLTag.length(), HTMLTag))
		throw runtime_error("Not an HTML file");

	// Get the base url
	char* curlBaseUrl;
	ret = curl_easy_getinfo(curlh, CURLINFO_EFFECTIVE_URL, &curlBaseUrl);
	if (ret != CURLE_OK)
		throw runtime_error(curlErr);
	if (!curlBaseUrl)
		throw runtime_error("No base url");
	baseUrl = string(curlBaseUrl);
}

// Parses the raw HTML content to extract tags and urls. On success,
// fills the internal data members string text and vector<> urls. If
// an error occurs, an exception is thrown.
void SimpleHTMLParser::parseHTML() {
	enum { START, TAG, SCRIPT, ANCHOR, HREF,
	       COMMENT, FRAME, SRC, STYLE, ENTITY } state;

	state = START;	// Current state
	string url;		// URL found within HTML content

	const char* b = html.data();
	const char* bufferEnd = b + html.length();
	bool lastCharSpace = false;
	bool lastCharText = false;
	while (b < bufferEnd) {
		//printf("<%c,%d,%d>", *b, *b,state);
		switch (state) {
		case START: {
			if (match(&b,"<SCRIPT")) {
				state = SCRIPT;
				if (lastCharText) {
					onContentFound(' ');
					lastCharText = false;
				}
			}
			else if (match(&b,"<!--")) {
				state = COMMENT;
				if (lastCharText) {
					onContentFound(' ');
					lastCharText = false;
				}
			}
			else if (match(&b,"<A ")) {
				state = ANCHOR;
				if (lastCharText) {
					onContentFound(' ');
					lastCharText = false;
				}
			}
			else if (match(&b,"<FRAME ")) {
				state = FRAME;
				if (lastCharText) {
					onContentFound(' ');
					lastCharText = false;
				}
			}
			else if (match(&b,"<STYLE")) {
				state = STYLE;
				if (lastCharText) {
					onContentFound(' ');
					lastCharText = false;
				}
			}
			else if	(match(&b,"<")) {
				state = TAG;
				if (lastCharText) {
					onContentFound(' ');
					lastCharText = false;
				}
			}
			else if (match(&b,"&")) {
				state = ENTITY;
				lastCharText = false;
			}
			else {
				char c = *b;
				// Substitute one or more blank chars with a single space
				if (c=='\n'||c=='\r'||c=='\t'||c==' ') {
					if (!lastCharSpace) {
						onContentFound(' ');
					}
					lastCharSpace = true;
					lastCharText = false;

				// Skip most punctuation
				} else if (!(c=='.'||c==','||c==';'||c==':'||c=='!'||c=='?'
					||c=='('||c==')'||c=='{'||c=='}'||c=='['||c==']'
					||c=='-'||c=='^'||c=='\"'||c=='|'||c=='#'||c=='$'
					||c=='-'||c=='\''||c=='%')) {
					// Output lowercase characters only
					onContentFound(tolower(c));
					lastCharSpace = false;
					lastCharText = true;
				}

				b++;
			}
			break;
		}
		case ANCHOR: {
			if (match(&b,"href=\"")) {
				state = HREF;
				url = "";
			}
			else if (match(&b,">")) {
				// End script
				state = START;
			}
			else {
				b++;
			}
			break;

		}
		case HREF: {
			if (match(&b,"\"")) {
				// Found ending "
				state = ANCHOR;
				onAnchorFound(url);
			}
			else {
				url.append(b, 1);
				b++;
			}
			break;
		}
		case FRAME: {
			if (match(&b,"src=\"")) {
				state = SRC;
				url = "";
			}
			else if (match(&b,">")) {
				// End script
				state = START;
			}
			else {
				b++;
			}
			break;

		}
		case SRC: {
			if (match(&b,"\"")) {
				// Found ending "
				state = FRAME;
				onAnchorFound(url);
			}
			else {
				url.append(b, 1);
				b++;
			}
			break;
		}
		case SCRIPT: {
			if (match(&b,"/SCRIPT>")) {
				// End script
				state = START;
			}
			else {
				b++;
			}
			break;
		}
		case COMMENT: {
			if (match(&b,"-->")) {
				// End comments
				state = START;
			}
			else {
				b++;
			}
			break;
		}
		case STYLE: {
			if (match(&b,"/STYLE>")) {
				// End style
				state = START;
			}
			else {
				b++;
			}
			break;
		}
		case TAG: {
			if (match(&b, ">")) {
				state = START;
			}
			else {
				b++;
			}
			break;
		}
		case ENTITY: {
			if (match(&b, ";")) {
				state = START;
			} else {
				b++;
			}
			break;
		}
		default:;
		}
	}
}

// Determines whether the substring pointed to by *b matches the
// passed string m, in a case-insensitive manner. If there's a match,
// *b is advanced to the position after the matching substring.
// Otherwise, *b is not modified.
bool SimpleHTMLParser::match(const char **b, string m) {
	// Get substring, convert to all-caps
	string bstr(*b, m.length());
	for (auto& c : bstr) c = toupper(c);
	for (auto& c : m) c = toupper(c);

	// Compare with match string
	if (bstr == m) {
		(*b)+=m.length();
		return true;
	}
	return false;
}

// Decomposes a URL into its component parts
void SimpleHTMLParser::decomposeUrl(string url, string& scheme,
	string& netloc, string& query, string& params, string& path) {
	// Extract and discard the fragment identifier
	size_t fragPos = url.find("#");
	url = url.substr(0, fragPos);

	// Parse the scheme
	scheme = "";
	string schemeChars = "abcdefghijklmnopqrstuvwxyz"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789+.-";
	size_t schemeColonPos = url.find(":", 1);
	if (schemeColonPos != string::npos) {
		string schemeName = url.substr(0, schemeColonPos);
		if (schemeName.find_first_not_of(schemeChars) == string::npos) {
			scheme = schemeName;
			url = url.substr(schemeColonPos+1);
		}
	}

	// Parse the network location
	netloc = "";
	size_t dblSlashPos = url.find("//");
	if (dblSlashPos == 0) {
		size_t nextSlashPos = url.find("/", 2);
		if (nextSlashPos != string::npos) {
			netloc = url.substr(2, nextSlashPos - 2);
			url = url.substr(nextSlashPos);
		} else {
			netloc = url.substr(2);
			url = "";
		}
	}

	// Parse the query information
	query = "";
	size_t qmarkPos = url.find("?");
	if (qmarkPos != string::npos) {
		query = url.substr(qmarkPos+1);
		url = url.substr(0, qmarkPos);
	}

	// Parse the parameters
	params = "";
	size_t semicolonPos = url.find(";");
	if (semicolonPos != string::npos) {
		params = url.substr(semicolonPos+1);
		url = url.substr(0, semicolonPos);
	}

	// All that remains is the path (including a possible leading slash)
	path = url;
}

// Combine decomposed URL parts into an absolute URL
string SimpleHTMLParser::combineUrl(string scheme, string netloc,
	string query, string params, string path) {
	string url = scheme + "://" + netloc;
	if (path.find("/") == 0)
		url = url + path;
	else
		url = url + "/" + path;
	if (!params.empty())
		url = url + ";" + params;
	if (!query.empty())
		url = url + "?" + query;
	return url;
}

// Converts the relative url to an absolute url using the base
// url from the parsed HTML file. The code here follows the algorithm
// described in RFC 1808, sections 2 and 4:
// https://tools.ietf.org/html/rfc1808
string SimpleHTMLParser::getAbsoluteUrl(string url) {
	string newUrl;

	// If there's no base URL, assume this url is absolute
	if (baseUrl.empty()) {
		newUrl = url;
		return newUrl;
	}

	// If the relative URL is empty, it's equal to the base URL
	if (url.empty()) {
		newUrl = baseUrl;
		return newUrl;
	}

	// Decompose the base url and relative url
	string baseScheme, baseNetloc, baseQuery, baseParams, basePath;
	string scheme, netloc, query, params, path;
	decomposeUrl(baseUrl, baseScheme, baseNetloc, baseQuery,
		baseParams, basePath);
	decomposeUrl(url, scheme, netloc, query, params, path);

	// If relative URL starts with a scheme, it's an absolute URL
	if (!scheme.empty()) {
		newUrl = url;
		return newUrl;
	}
	// Otherwise, inherit the base scheme
	scheme = baseScheme;

	// If relative URL's network location is non-empty, recombine
	if (!netloc.empty()) {
		newUrl = combineUrl(scheme, netloc, query, params, path);
		return newUrl;
	// Otherwise, inherit from base network location
	} else {
		netloc = baseNetloc;
	}

	// If relative URL's path is preceded by a slash, recombine
	if (path.find("/") == 0) {
		newUrl = combineUrl(scheme, netloc, query, params, path);
		return newUrl;
	}

	// If relative URL's path is empty, inherit base URL path
	if (path.empty()) {
		path = basePath;

		// If params is non-empty, recombine
		if (!params.empty()) {
			newUrl = combineUrl(scheme, netloc, query, params, path);
			return newUrl;
		// Otherwise, inherit base URL params
		} else {
			params = baseParams;

			// If query is non-empty, recombine
			if (!query.empty()) {
				newUrl = combineUrl(scheme, netloc, query, params, path);
				return newUrl;
			// Otherwise, inherit base URL query and then recombine
			} else {
				query = baseQuery;
				newUrl = combineUrl(scheme, netloc, query, params, path);
				return newUrl;
			}
		}
	}

	// Remove the last segment of the base path
	size_t lastSlashPos = basePath.find_last_of("/");
	string newPath = "";
	if (lastSlashPos != string::npos)
		newPath = basePath.substr(0, lastSlashPos+1);
	newPath = newPath + path;

	// Remove all occurences of "./" if it's a complete path segment
	size_t sp = 0, segPos;
	while ((segPos = newPath.find("./", sp)) != string::npos) {
		if (segPos == 0 || newPath[segPos-1] == '/') {
			newPath.erase(segPos, 2);
			sp = 0;
		} else {
			sp = segPos + 1;
		}
	}

	// Remove a trailing "." if it's a complete path segment
	if (newPath.find_last_of(".") == newPath.length() - 1 &&
		(newPath.length() == 1 || newPath[newPath.length() - 2] == '/'))
		newPath = newPath.substr(0, newPath.length() - 1);

	// Remove all occurences of "<segment>/../"
	while ((segPos = newPath.find("/../")) != string::npos && segPos > 0) {
		size_t prevSlashPos = newPath.find_last_of("/", segPos - 1);
		if (prevSlashPos == string::npos) {
			newPath = newPath.substr(segPos+4);
		} else {
			newPath.erase(prevSlashPos+1, segPos+4-(prevSlashPos+1));
		}
	}

	// Remove a trailing "<segment>/.."
	if (newPath.substr(newPath.length()-3) == "/..") {
		size_t prevSlashPos = newPath.find_last_of("/", newPath.length()-4);
		if (prevSlashPos == string::npos) {
			newPath = "";
		} else {
			newPath = newPath.substr(0, prevSlashPos+1);
		}
	}

	// Set the new path
	path = newPath;

	// Recombine final url
	newUrl = combineUrl(scheme, netloc, query, params, path);
	return newUrl;
}

// Adds to the HTML content without tags
void SimpleHTMLParser::onContentFound(char c) {
	text.push_back(c);
}

// Convert a relative URL into an absolute URL and add it to the list
// of urls
void SimpleHTMLParser::onAnchorFound(string url) {
	// Get the absolute url
	string absUrl = getAbsoluteUrl(url);

	// Only store urls with http(s) scheme
	string scheme, n, q, p, p2;
	decomposeUrl(absUrl, scheme, n, q, p, p2);
	if (scheme != "http" && scheme != "https")
		return;

	// Store the url
	urls.push_back(getAbsoluteUrl(url));
}
