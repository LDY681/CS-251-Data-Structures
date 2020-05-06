#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "SimpleHTMLParser.h"
#include "RBTree.h"
#include "Node.h"

using namespace std;

// Input stream operator overload for node elements
istream& operator>>(istream& in, vector<pair<string, int>>& e);
//find intersection and put to the list

vector <pair <string, int>>* intersection(vector<vector<pair<string, int>>>* vec);
vector <pair <string, int>>* sort(vector <pair <string, int>>* intersect);
bool compare(pair<string, int> i, pair<string, int> j);

int main(int argc, char** argv) {
	if (argc > 7 || argc < 3) {
		cout << "Usage: search.org RBTree phrase" << endl;
		cout << "  Phrase must be between 1 and 5 words" << endl;
		return 0;
	}

	//CASE Failed to open RBTree file!
	string infile = argv[1];
	std::filebuf in;
	if (!in.open(infile, std::ios::in)) {
		std::cout << "Failed to open RBTree file!" << std::endl;
		return 0 ;
	}
	std::istream fin(&in);

	//Populate a RBtree with filename from argv[1]
	RBTree<string, vector<pair<string, int>>> wordTree;
	fin >> wordTree;
	
	//a list of ​elements
	vector<vector<pair<string, int>>>* vec = new vector<vector<pair<string, int>>>();

	int idxofargc = 2;
	//cout << "argc is: " << argc << endl;
	while (idxofargc < argc) {
		//get word and tolower
		string word = argv[idxofargc];
		//cout << word << "  "<< idxofargc << endl;
		std::transform(word.begin(), word.end(), word.begin(), ::tolower);

		if (wordTree.search(word) != NULL) {
			//TODO: Get the element from the node
			vec->push_back( wordTree.search(word)->getElement() );
		}
		else {	//Put an empty element in the list 
			//CASE Not found
			cout << "Not found" << endl;
			return 0;
		}
		idxofargc++;
	}

	//TODO: check for error on &
	vector <pair <string, int>>* intersec = intersection(vec);

	sort(intersec->begin(), intersec->end(), compare);
	for (auto i = intersec->begin(); i != intersec->end(); ++i){
		cout << i->first << " " << i->second << endl;
	}
	return 0;
}

vector <pair <string, int>>* intersection(vector<vector<pair<string, int>>>* vec) {
	if (vec->size() == 0) {
		return NULL;
	}
	else if (vec->size() == 1) {
		vector <pair <string, int>>* front = &vec->front();
		return front;
	}
	else {
		vector <pair <string, int>>* front = &vec->front();
		int count = 0;
		for (auto& i : *vec) {
			if (count == 0) {
				count++;
				continue;
			}
			count++;
			vector <pair <string, int>>*temp = new vector <pair <string, int>>();

			for (auto& j : i) {
				for (auto &k : *front) {
					if (j.first == k.first) {
						//cout << "intersection happened:  " << j.first << "   " << j.second + k.second << endl;
						pair <string, int> PAIR = make_pair(j.first, j.second + k.second);	//intergrate the two and then do it recursively
						temp->push_back(PAIR);
					}
				}
			}
			front = temp;
		}
		return front;
	}

}


bool compare(pair<string, int> i, pair<string, int> j) {
	if (i.second == j.second) {
		string a = i.first;
		string b = j.first;
		if (a.compare(b) > 0) {
			return false;
		}
		else {
			return true;
		}
	}
	return (i.second > j.second);
}





// This function overloads the input stream operator for Node
// elements. It has been provided to you and does not need to be
// altered.
istream& operator>>(istream& in, vector<pair<string, int>>& e) {
	// Clear any existing contents
	e.clear();

	// Read the number of elements
	size_t n;
	in >> n;
	for (int i = 0; i < n; i++) {
		// Read each member of each pair the vector stores
		string u;
		in >> u;
		int f;
		in >> f;
		// Add to vector
		e.push_back(make_pair(u, f));
	}

	return in;
}
