#include <iostream>
#include "SimpleHTMLParser.h"
using namespace std;

// Example program to demonstrate using SimpleHTMLParser.

void printUsage() {
	cerr << "  Usage: gethtml [-h|-t|-a] url" << endl;
	cerr << "  Example: gethtml https://www.cs.purdue.edu" << endl;
}

int main( int argc, char ** argv ) {
	string option;
	string url;

	if (argc == 1) {
		printUsage();
		exit(1);
	} else if (argc == 2) {
		option = "";
		url = string(argv[1]);
	} else {
		option = string(argv[1]);
		url = string(argv[2]);
	}

	if (option == "-h") {
		printUsage();
		exit(1);
	}

	// Create a parsing context
	SimpleHTMLParser parser;

	// Attempt to parse a url
	if (!parser.parse(url)) {
		// Print the error if parsing failed
		cerr << parser.errmsg() << endl;
		exit(1);
	}

	if (option == "") {
		// No options, output raw HTML
		cout << parser.getHTML() << endl;
	} else if (option == "-t") {
		// Output text (with tags removed)
		cout << parser.getText() << endl;
	} else if (option == "-a") {
		// Get a list of URLs embedded in the HTML file
		vector<string> urls = parser.getUrls();
		// Print each URL
		for (auto& u : urls)
			cout << u << endl;
	}

	return 0;
}
