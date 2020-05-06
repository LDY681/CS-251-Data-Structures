#ifndef DECODER_H
#define DECODER_H
#include <fstream>
#include <string>
#include <cmath>  
#include "MinHeap.h"
#include "TreeNode.h"
#include "HuffTree.h"
#include <iostream>
#include "Decoder.h"
#include <sstream>
#include <bitset>

using namespace std;



class Decoder
{
	private:
		unsigned frequency_table[256];
		string fpstr;	//filepath
		int numuniq;	//number of unique characters
		ifstream myfile;
		int numbody;
		HuffTree* htree;
		string outtofile;
		stringstream out;
		// You need to add more class memeber and methods

	public:
		//huff_file_path is the input (encoded) file that we 
		//want to decode
		Decoder(string huff_file_path);

		//UPDATE: change this type to stringstream
		stringstream iteratetrustring(string str);

		//Fills up the frequency_table array where frequency_table[i] 
		//will contain the frequency of char with ASCII code i			
		//This method will read the header of the encoded file to 
		//extract the chars and their frequency
		void buildFrequencyTableFromFile(short s, ifstream &myfile);
		//Overall decode function
		void decode();
		//Creates a min-heap and builds the Huffman tree
		void decodeheader(string file_path);
		//Creates a min-heap and builds the Huffman tree
		void decodebody(ifstream &myfile);

		MinHeap* buildminheap(MinHeap *mh);

		//Writes the uncompressed file and save it as file_path
		void writeUncompressedFile(string file_path);

		~Decoder();
		stringstream readchar(ifstream &myfile);
		int codetablecompare(string* codetable, string substr);


};

#endif
