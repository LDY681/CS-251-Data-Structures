#ifndef ENCODER_H
#define ENCODER_H

#include "MinHeap.h"
#include "HuffTree.h"
#include "MinHeap.h"
#include <string>
#include "TreeNode.h"

using namespace std;

class Encoder
{
	private:
		string fpstr;
		unsigned frequency_table[256];
		string binary;
			// You need to add more class memeber and methods
	public:
		//test_file_path is the input (decoded) file
		Encoder(string file_path); 
		
		//Fills up the frequency_table array where frequency_table[i] 
		//will contain the frequency of char with ASCII code i		
		void buildFrequencyTable(); 
			
		//Create minheap
		MinHeap* createminheap(MinHeap * mh);

		//Builds the min head and run the encoding algorithm
		void encode();

		//Generates the encoded file and save it as output_file_path
		void writeEncodedFile(string output_file_path);

		//listedfile
		void createlistedfile(HuffTree * htree);

		~Encoder();
};

#endif
