#ifndef SIMPLEHTMLPARSER_H
#define SIMPLEHTMLPARSER_H

#include <string>
#include <vector>
#include <curl/curl.h>

// This class implements a simple HTML parser
class SimpleHTMLParser {
public:
	// Constructor / destructor
	SimpleHTMLParser();
	~SimpleHTMLParser();

	// Download and parse an HTML file
	bool parse(std::string url);

	// Call these after parsing an HTML file
	std::string getBaseUrl() const { return baseUrl; }
	std::string getHTML() const { return html; }
	std::string getText() const { return text; }
	std::vector<std::string> getUrls() const { return urls; }
	std::string errmsg() const { return error; }

protected:
	CURL* curlh;		// Handle to curl context
	std::string baseUrl;	// Last-used base URL
	std::string html;		// Raw HTML content
	std::string text;		// HTML content with tags removed
	std::vector<std::string> urls;	// List of urls in HTML file
	std::string error;		// Stores a description of the last error
	std::string curlErr;	// Buffer for libcurl errors

	// Helper functions
	void fetchHTML(std::string url);	// Download an HTML file
	void parseHTML();					// Parse the raw HTML
	bool match(const char **b, std::string m);
	void decomposeUrl(std::string url, std::string& scheme,
		std::string& netloc, std::string& query, std::string& params,
		std::string& path);
	std::string combineUrl(std::string scheme, std::string netloc,
		std::string query, std::string params, std::string path);
	std::string getAbsoluteUrl(std::string url);

	// Callbacks
	void onContentFound(char c);
	void onAnchorFound(std::string url);
};

#endif

