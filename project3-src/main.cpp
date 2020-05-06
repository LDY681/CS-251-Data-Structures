#include <iostream>
#include <string>
#include "MinHeap.h"
#include "Encoder.h"
#include "Decoder.h"
#include <string.h>

using namespace std;

void printHelp(){
	cout << "Invalid arguments." << endl;
	cout << "Type \"huffman [mode] [arguments]\" where mode and its arguments are one of the following:" << endl;
	cout << "-e [src] [dest]: encode the source file and place the result into the specified destination" << endl;
	cout << "-d [src] [dest]: decode the source file and place the result into the specified destination" << endl;
	exit(1);
}


int main (int argc, char** argv){
	if (argc != 4) {
		printHelp();
	}

	string option = argv[1];
	string src = argv[2];
	string dest= argv[3];

	if ( option.compare("-e") == 0) {
		//call encoder
		Encoder * enc = new Encoder(src);
		enc->buildFrequencyTable();
		enc->encode();	
		enc->writeEncodedFile(dest);
		enc->~Encoder();
	}
	else {
		//call decoder
		Decoder * dec = new Decoder(src);	
		dec->decode(); ///JUMP!!!!!!!!!!!!!!!!!!!!!!!!!!!
		dec->writeUncompressedFile(dest);
		dec->~Decoder();
	}

	return 0;
}