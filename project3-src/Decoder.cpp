#include <iostream>
#include "Decoder.h"
#include <string>
#include <fstream>
#include <cmath>  
#include "MinHeap.h"
#include "TreeNode.h"
#include "HuffTree.h"
#include <sstream>
#include <bitset>

unsigned frequency_table[256];

Decoder::Decoder(string huff_file_path) {
	fpstr = huff_file_path;
	numuniq = 0;	//number of unique character
	numbody = 0;
	htree = new HuffTree();
}

//Fills up the frequency_table array where frequency_table[i] 
//will contain the frequency of char with ASCII code i			
//This method will read the header of the encoded file to 
//extract the chars and their frequency
void Decoder::buildFrequencyTableFromFile(short s, ifstream &myfile) {
	unsigned char c = 0;
	int freqbyte = 0;
	int i1 = 0;
	//TODO: check if char with ascii value between 128 and 255 works!
	while (i1 < s && myfile.read((char*)&c, 1) && myfile.read((char*)&freqbyte, 4)) {
		//cout << "PRINT ASCII value:  " << (int)c << endl;
		//cout << "PRINT frequency:  " << freqbyte << endl;
		frequency_table[(int)c] = freqbyte;
		//cout << "PRINT value of counter i1: " << i1 << endl;
		i1++;
	}
	return;
}

void Decoder::decode() {
	decodeheader(fpstr); ///JUMP!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

//PERFECT! decode header(get uniq char number + build freuqency_table)
void Decoder::decodeheader(string fpstr) {
	ifstream myfile;
	myfile.open(fpstr);
	//cout << "the file path is:   " << fpstr << endl;

	//GET UNIQ NUMBER
	short s;
	myfile.read((char*)&s, 2);
	//cout << "unique number is:   " << s << endl;
	buildFrequencyTableFromFile(s, myfile);
	//READ CHAR AND FREQUENCY and store in frequency table

	decodebody(myfile);	///JUMP!!!!!!!!
}

//PERFECT! build minheap from frequency_table
MinHeap * Decoder::buildminheap(MinHeap *mh){	
	int i2;
	for (i2 = 0; i2 < 256; i2++) {
		if (frequency_table[i2] != 0) {
			TreeNode * tn = new TreeNode(i2, frequency_table[i2]);
			mh->insert(tn);
		}
	}	
	return mh;
}
	
//build minheap and build hufftree and read body as char into string
void Decoder::decodebody(ifstream &myfile) {
	//STEP2:build minheap from frequency_table
	MinHeap * mh = new MinHeap();
	MinHeap * mmh = buildminheap(mh);

	//Create hufftree from minHeap, htree->htree
	htree = new HuffTree();
	htree->buildTree(mmh);
	int arr[999];
	int top = 0;
	htree->generateCodes(htree->htree, arr, top);

	//body stringstream
	stringstream ss = readchar(myfile);
	string str = ss.str();	//body in a string of chars
	//cout << "The body string is(in char):  " << str << endl;
	//TODO: UPDATE
	out = iteratetrustring(str);	///JUMP!!!!!!!!!!!!!!!!!!!!!!!!!!!

	myfile.close();

	//UPDATE
	//delete mh;
	//delete mmh;
}

stringstream Decoder::readchar(ifstream &myfile) {
	stringstream ss;
	unsigned char c = 0;
	while (myfile.read((char*)&c, 1)) {
		ss << c; //c is some char
		numbody++;
	}
	return ss;
}

//UPDATE change type to stringstream
//iterate thru string and find out 
stringstream Decoder::iteratetrustring(string str) {
	stringstream out; //the output stringstream
	TreeNode * root = htree->htree;
	int freq = htree->htree->getFrequency();
	int freqcount = 0;

	int i;
	for (i = 0; i < numbody; i++) {
		bitset<8> bit = str[i];
		string bitstring = bit.to_string();
		//cout << "The bitstring is :  " << bitstring << endl;
		int j;
		for (j = 0; j < 8; j++) {
			if (freqcount == freq) {
				
			}else{
			if (root->isLeafNode()) {
				freqcount++;
				//cout << "The val is " << root->getVal() << endl;
				out << (unsigned char)root->getVal();
				root = htree->htree;
			}
			if (bitstring[j] == '1') {
				root = root->getLeft();
			}
			if (bitstring[j] == '0') {
				root = root->getRight();
			}
			//j++;
			}
		}
		//i++;
		if (freqcount == freq) {
			i = numbody + 1;
		}
		
	}

	//UPDATE 
	//delete root;
	return out;
}

//iterate through hufftree

int Decoder::codetablecompare(string* codetable, string substr) {
	int i;
	for (i = 0; i < 256; i++) {
		if (substr.compare(codetable[i]) == 0) {
			return i;
		}
	}
	return -1;
}

//Writes the uncompressed file and save it as file_path
void Decoder::writeUncompressedFile(string file_path) {
	ofstream myfile;
	myfile.open(file_path);
	myfile << out.rdbuf();
	//myfile << outtofile;
	myfile.close();

}

Decoder::~Decoder() {
	//delete htree;
}


