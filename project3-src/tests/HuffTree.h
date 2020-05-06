#ifndef HUFFTREE_H
#define HUFFTREE_H

#include "MinHeap.h"
#include "TreeNode.h"
#include <string>

#define MAXCODELENGTH 256
#define BYTESIZE 8

using namespace std;

class HuffTree
{
	private:
		friend class Encoder; 
		friend class Decoder;
		TreeNode * htree;
		TreeNode * iter;
		char *bitcode;
		int index;
		MinHeap *mmh;
		string * huffcode;
		int huffcodeidx;

		string* codetable;
		//Add class members and methods	

	public:
		HuffTree();

		//build a hiffman  tree  give a minheap
		void buildTree(MinHeap * mh);

		//generate codes by traversing the huffman tree
		//and store them in an internal data structure (array of strings for example)
		void generateCodes(TreeNode * root, int arr[], int top);

		//returns root of the tree
		TreeNode * getRoot();

		string int2string(int arr[], int top);

		//generatebody
		string generatebody(string txtpath);
		//generateheader
		string generateheader(unsigned frequency_table[256]);

		//char to binary
		string char2binary(int a, int num);

		//number of uniq chars
		int numofuniq(unsigned frequency_table[256]);

		//returns huffman code from  the ascii code
		string getCharCode(int c);

		//rellocate eight zeros
		void relocateeightzeros(string &str, int num);

		~HuffTree();
		
};


#endif