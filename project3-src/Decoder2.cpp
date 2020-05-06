#include <iostream>
#include "Decoder.h"
#include <string>
#include <fstream>
#include <cmath>  
#include "MinHeap.h"
#include "TreeNode.h"
#include "HuffTree.h"

unsigned frequency_table[256];

Decoder::Decoder(string huff_file_path) {
	fpstr = huff_file_path;
	numuniq = 0;	//number of unique character
}

//Fills up the frequency_table array where frequency_table[i] 
//will contain the frequency of char with ASCII code i			
//This method will read the header of the encoded file to 
//extract the chars and their frequency
void Decoder::buildFrequencyTableFromFile() {

}

//Overall Decoder
void Decoder::decode() {
	//numuniq = decodeuniq(fpstr);
	//lets decode header
	decodeheader(fpstr);
	//lets decode body
	decodebody(fpstr);
}

//TODO: passing ifstream as argument, check if worked!
//decode unique number char bytes and return the number of unique number  
int Decoder::decodeuniq(string fpstr) {
	ifstream myfile;
	myfile.open(fpstr);

	short s;
	myfile.read((char*)&s, 2);

	cout << "check is uniq number is printing OK:  " << s << endl;
	return s;
	//myfile.close();
}

//TODO: passing ifstream as argument, check if worked!
//Creates a min-heap and builds the Huffman tree
void Decoder::decodeheader(string fpstr) {
	ifstream myfile;
	myfile.open(fpstr);
	cout << "the file path is:   " << fpstr << endl;

	//GET UNIQ NUMBER
	short s;
	myfile.read((char*)&s, 2);
	cout << "unique number is:   " << s << endl;

	//READ CHAR AND FREQUENCY and store in frequency table
	unsigned char c = 0;
	int freqbyte = 0;
	
	int i1 = 0;
	while (i1 < s && myfile.read((char*)&c, 1) &&myfile.read((char*)&freqbyte, 4) ) {
		cout << "to see it went into the while loop" << endl;
		//myfile.read((char*)&c, 1);
		//myfile.read((char*)&freqbyte, 4);
	
		cout << "PRINT ascci value:  " << (int)c << endl;
		cout << "PRINT frequency:  " << freqbyte << endl;

		frequency_table[(int)c] = freqbyte;
	
		cout << "PRINT value of counter i1: " << i1 << endl;
		i1++;
	}

	//STEP2:build minheap from frequency_table
	MinHeap * mh = new MinHeap();
	MinHeap * mmh = buildminheap(mh);

	//Create hufftree from minHeap, htree->htree
	HuffTree* htree = new HuffTree();
	htree->buildTree(mmh);
	decodebody(myfile);

}

//TODO: check for errors Create minheap from frequency_table
//build minheap from frequency_table
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
	

void Decoder::decodebody(ifstream &myfile) {

	//Read all bits left to a string

	//TODO: test end of file condition
	unsigned char bit_buffer;
	
/*
Unsigned char bit_buffer; //this is the byte we use to write into the file


for each input char c in the decoded file do
	string code = get huffman code (c)
	for each character b in code do
		bit_buffer = bit_buffer << 1; //we shift the bit_buffer 1 position to the left because we want to insert a bit in the right-most position
		bit_buffer bit_buffer | (b - '0') // we do a bit-wise OR between the read bit (b) and the bit_buffer. Notice the conversion from the ASCII code to the decimal number

		if (number of written bits in bit_buffer == 8)
			write bit_buffer into the file
			reset the number_written_bits to 0
			reset the bit_buffer to 0
		endif
	done
done

pad the bit buffer if necessary
*/
}

//Writes the uncompressed file and save it as file_path
void Decoder::writeUncompressedFile(string file_path) {

}

Decoder::~Decoder() {
	//TODO:
}

