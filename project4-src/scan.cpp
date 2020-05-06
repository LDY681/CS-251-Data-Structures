#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "SimpleHTMLParser.h"
#include "RBTree.h"

using namespace std;

// Output stream operator overload for node elements
ostream& operator<<(ostream& out, const vector<pair<string, int>>& e);

int main(int argc, char** argv) {
	//Argument check
	if (argc != 3) {
		cout << "Usage: scan.org inputfile outputfile" << endl;
		return 0;
	}

	//Varible assignment
	string input = argv[1];
	string output = argv[2];
	ifstream infile;
	infile.open(input);
	ofstream outfile;
	outfile.open(output);
	SimpleHTMLParser *sp = new SimpleHTMLParser();
	RBTree<string, vector<pair<string, int>>> *rb = new RBTree<string, vector<pair<string, int>>>();
	string urlline;

	//TEST
	//sp->parse("https://my.cs.purdue.edu/");
	//cout << "Testing parse and getText on https://my.cs.purdue.edu/ " << endl;
	//cout << sp->getText() << endl;
	//string s = sp->getText();
	//cout << "Testing getText" <<  s << endl;
	//cout << endl;


	
	//get the number of urls
	getline(infile, urlline);

	stringstream ss(urlline);
	int numurl = 0;
	ss >> numurl;
		//cout << " number of urls is: " << numurl << endl;
	int count = 0;
	while (count < numurl) {

		//get url from urls1.txt as a string 
		getline(infile, urlline);

			//cout << "Testing: print urls: " << urlline << endl;

		//execute if parse successful (valid url)
		if (sp->parse(urlline)) {

			//get text and store in string s 
			string s = sp->getText();

				//cout << "Testing getText" <<  s << endl;

			stringstream ss(s);
			string word;

			//iterate through string
			while (!ss.eof()) {
				word = "";
				ss >> word;
				if (word != "") {
						//cout << "See what word will be: " << word << endl;

					//search for the word as key

					//CASEA: if word is not found, make pair push it to the vector and insert the node

					if (rb->search(word) == NULL) {
						//cout << word << " is not found, insert new Node" << endl;
						pair <string, int > PAIR = make_pair(urlline, 1);
						vector<pair <string, int>> vec;
						vec.push_back(PAIR);
						rb->insert(word, vec);

					}
					//CASEB: if word is found
					else {
						vector<pair <string, int>>& vec = rb->search(word)->getElement();
						bool urlfound = false;	//check is urlexist in the vector


						//CASE1: check if url exists, increment frequency
						int count = 0;
						for (pair <string, int>& object : vec) {

							if (object.first == urlline) {	//if url exists
								//cout << word << " is found and url exists, increase frequency by 1" << endl;
								//cout << "check frequency before: " << object.second << endl;
								object.second++;
								urlfound = true;
								//cout << "check frequency after : " << object.second << endl;
							}
						}

						//CASE2: check is url doesnt exists, make pair and add it to the vector
						if (urlfound == false) {
							//cout << word << " is found but url doesnt exists, push new pair in " << endl;
							pair <string, int > PAIR = make_pair(urlline, 1);
							//vector<pair <string, int>> vec;
							vec.push_back(PAIR);
						}
					}
				}
			}
		}
		count++;
	}
	outfile << *rb << endl;
	outfile.close();
	//rb->inorder(outfile);
	return 0;
}


// This function overloads the output stream operator for Node
// elements. It has been provided to you and does not need to be
// altered.
ostream& operator<<(ostream& out, const vector<pair<string, int>>& e) {
	// Write the number of elements in the vector
	out << e.size() << endl;
	for (auto& uf : e)
		// Write each member of each pair the vector stores
		out << uf.first << " " << uf.second << endl;
	return out;
}
