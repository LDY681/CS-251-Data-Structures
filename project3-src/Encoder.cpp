#include <iostream>
#include <fstream>
#include "Encoder.h"
#include "HuffTree.h"
#include <cmath>

using namespace std;

		//unsigned frequency_table[256];
		// You need to add more class memeber and methods
		//test_file_path is the input (decoded) file
		Encoder::Encoder(string file_path) {
			fpstr = file_path;
			int i;
			for (i = 0; i < 256; i++) {
				frequency_table[i] = 0;
			}
		}

		//Fills up the frequency_table array where frequency_table[i] 
		//will contain the frequency of char with ASCII code i		
		void Encoder::buildFrequencyTable() {
			ifstream myfile;
			myfile.open(fpstr);
			
			//CAST CHAR TO UNSIGNED CHAR 
			/*UPDATE
			char c;
			while (myfile.get(c)) {	//get char each time
				unsigned char cc = (unsigned char)c;
				frequency_table[cc]++;
			}
			*/


			unsigned char c;
			while (myfile.read((char*)&c, 1)){
				frequency_table[c]++;
			}

			//close fstream
			myfile.close();
			return;
		}

		//main will call this function is argument is -e
		//Builds the min head and run the encoding algorithm
		void Encoder::encode() {

			//create MinHeap
			MinHeap *mh = new MinHeap();
            mh = createminheap(mh);
		       
			//Create HuffTree bases on minHeap
			HuffTree * htree = new HuffTree();
			htree->buildTree(mh);
			int arr[999];
			int top = 0;
			htree->generateCodes(htree->htree, arr, top);

			//write huffcode in 010101 form into listedfile.txt for test reasons
			createlistedfile(htree);
			
			//binary = header + body
			string body = htree->generatebody(fpstr);
			string header = htree->generateheader(frequency_table);	///JUMP!!!
			binary = header + body;
			//cout << binary << endl;

			/*writencodedfile
			string str3("encoded");	//encoded
			std::size_t pos = fpstr.find(".txt");	
			string str4 = fpstr.substr(0, pos);	//filenamewithnoextension
			string str5(".huff");	//,huff
			string output_file_path = str3 + str4 + str5;
			writeEncodedFile(output_file_path);
			*/
			//TODO:close all file streams
			
		}

		void Encoder::createlistedfile(HuffTree * htree) {
			ofstream myfile;
			string str1("listed");
			string ofile = str1 + fpstr; //output file path
			myfile.open(ofile);
			int i = 0;
			while (!htree->huffcode[i].empty()) {
				myfile << htree->huffcode[i] << endl;
				i++;
			}
			myfile.close();
		}

        MinHeap* Encoder::createminheap(MinHeap * mh){
		    int idx = 0;
            for (idx = 0; idx < 256; idx++) {
				if (frequency_table[idx] != 0) {
					TreeNode * ins = new TreeNode( (unsigned char)idx, (unsigned)frequency_table[idx]);
					mh->insert(ins);
				}
			}
			return mh;
        }

		//Generates the encoded file and save it as output_file_path
		void Encoder::writeEncodedFile(string output_file_path) {
			ofstream myfile;
			myfile.open(output_file_path);
			int trunc = 0;
			while (trunc < binary.size() ) {
				string sub = binary.substr(trunc, 8);	//take 8 bits
				const char *cstr = sub.c_str();
				

				char* charnum = new char[1024];
				charnum[0]= (int)((sub[0]-'0') * pow(2, 7) + (sub[1] - '0') * pow(2, 6) + (sub[2] - '0') * pow(2, 5) + (sub[3] - '0') * pow(2, 4)+ (sub[4] - '0')*pow(2, 3)+ (sub[5] - '0')*pow(2, 2)+ (sub[6] - '0')*pow(2, 1)+ (sub[7] - '0')*pow(2,0));
				myfile.write(charnum, 1);
				trunc += 8;
			}
			
			myfile.close();
			return;
		}

		Encoder::~Encoder() {
		
		
		}


