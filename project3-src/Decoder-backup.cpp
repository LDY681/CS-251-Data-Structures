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
	outtofile = "";
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
	outtofile = iteratetrustring(str);	///JUMP!!!!!!!!!!!!!!!!!!!!!!!!!!!

	myfile.close();

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

//TODO:check correct?
//iterate thru string and find out 
string Decoder::iteratetrustring(string str) {
	int freq = htree->htree->getFrequency();
	int freqcount = 0;
	//TO DELETE
	ofstream test; 
	test.open("test.txt");
	int tcount = 0;

	int stri = 0;	//string index
	int biti = 0;	//bitset starting index
	int len = 1;	//length
	int count = 0;
	stringstream out; //the output stringstream

	while (stri < numbody) {	//while string index is less than the total length of body
		bitset<8> bit = str.c_str()[stri];	//the bitset at index i of stirng
		//cout << "Print bitset: " << bit << endl;
		string bitstring = bit.to_string();	//string of 8 (0s and 1s)
		//cout << "Print bitstring: " << bitstring << endl;

		if (biti % 8 == 0 && biti != 0 ) {	//last bit case
				stri++;
				bitset<8> bit = str.c_str()[stri];
				biti = 0;
				len = 1;
				bitstring = bit.to_string();
				// TO DELETE 
				//cout << "the new bitstring is : (case last bit in byte)" << bitstring << endl;

		}


		string substr = bitstring.substr(biti, len);
		int i = codetablecompare(htree->codetable, substr);
	
		while ( i == -1) {	//while substr no match codetable
			if ( (len + biti) %8 == 0) {
				stri++;
				bitset<8> bit2 = str.c_str()[stri];
				string bitstring2 = bit2.to_string();
				bitstring = bitstring + bitstring2;
				//cout << "the new bitstring is (case continous bits between byte) :" << bitstring << endl;

				//TO DELETE
				substr = bitstring.substr(biti, len);
				//cout << "the substr is  : " << substr << endl;
				i = codetablecompare(htree->codetable, substr);
			}
			if (i == -1) { len++; }
			substr = bitstring.substr(biti, len);
			//cout << "the substr is  : " << substr << endl;

			i = codetablecompare(htree->codetable, substr);
			//cout << "i is :   " << i << endl;

		}

		// TO DELETE 
		//cout << "the matching substr is: " << substr << " The char is: " <<  i << endl;
		//cout << "biti is ==" << biti << "    len is ==" << len << endl;
		//after find matching code

		//cout << "The LOCATION OF CHAR IS!!!!:   " << ++count << endl;
		//cout << "***************THE STRING IS NOW:    ****************** "  <<   out.str() << endl;


		//UPDATE
		//dont read if reach end of file
		freqcount++;
		if (freqcount != freq+1) {
			out << (unsigned char)i;
		}
		

		//UPDATE TO DELETE
		//case '\n'
		//if (stri == numbody - 1 && i == 10) {stri = numbody + 1;}

		biti = biti + len;
		len = 1;

		//UPDATE
		if (biti == 16 && len == 1 ) {
			stri++;
			biti = 0;
		}
		if (biti == 24 && len == 1) {
			stri = stri+2 ;
			biti = 0;
		}
		if (biti == 32 && len == 1) {
			stri = stri + 3;
			biti = 0;
		}


		if (biti >= 9) {
			biti = biti % 8;
			len = 1;
		}

		//cout << "stri == " << stri << endl;

		//UPDATE
		//break when count == freq
		if (freqcount == freq+1) {
			stri = numbody + 1;
		}
	}
	
	string stringout = out.str();

	//TO DELETE
	test.close();
	return stringout;
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
	myfile << outtofile;
	myfile.close();
}

Decoder::~Decoder() {
	//TODO:
}

