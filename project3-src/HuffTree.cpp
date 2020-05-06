#include <iostream>
#include "HuffTree.h"
#include <string>
#include <sstream>
#include <fstream>
#include "Encoder.h"
#include "string.h"

HuffTree::HuffTree() {
	htree = new TreeNode(0, 0);
	iter = htree;	//iterator
	bitcode =  new char[9999];
	index = 0;
	huffcode = new string[256];
	huffcodeidx = 0;
	mmh = new MinHeap();
	codetable = new string[256];
}

//build a hiffman tree give a minheap
void HuffTree::buildTree(MinHeap * mh) {
	mmh = mh;
	unsigned freq = 0;
	TreeNode *a;
	TreeNode *b;

	while ( mh->getSize() >= 2) {
		//extract two nodes from minheap
		a = mh->removeMin();
		b = mh->removeMin();
		freq = a->getFrequency() + b->getFrequency();

		//create internal node
		TreeNode *inter = new TreeNode('$', freq);
		inter->join(a, b);
		mh->insert(inter);
	}

	htree = mh->top();
	iter = htree;
	return;
}

//generate codes in format of binary code(101) + frequency and store in txt
//store them in code table
void HuffTree::generateCodes(TreeNode * root, int arr[], int top) {
	// Assign 1 to left edge and recur
	if (root->getLeft()) {
		arr[top] = 1; 
		TreeNode * next = root->getLeft();
		generateCodes(next, arr, top + 1);
	}

	// Assign 0 to right edge and recur
	if (root->getRight()) {
		arr[top] = 0;
		TreeNode * next = root->getRight();
		generateCodes(next, arr, top + 1);
	}

	// If this is a leaf node, then
	// it contains one of the input
	// characters, print the character
	// and its code from arr[]
	if ( root->isLeafNode() ) {
		//string of val
		string s1( to_string(root->getVal()) );
		//string of binary 101
		string s2 = int2string(arr, top);
		//string of frequency
		string s3 = ( to_string(root->getFrequency()) );
		//combination in format of binary code + frequency
		string combo = s1 + ' ' + s2 +' ' + s3 ;	
		//store string into huffcode
		huffcode[huffcodeidx] = combo;
		huffcodeidx++;
		codetable[(int)root->getVal()] = s2;
	}
}

string HuffTree::int2string(int arr[], int top) {
	string s;
	stringstream out;
	int i;
	for (i = 0; i < top; i++){
		out << arr[i];
	}
	s = out.str();
	return s;
}

//returns root of the tree
TreeNode * HuffTree::getRoot() {
	return htree;
}

//returns huffman code from  the ascii code //this is the bit code
string HuffTree::getCharCode(int c) {
	return codetable[c];	
}

//PERFECT
//read from txtfile and generate body string
string HuffTree::generatebody(string txtpath) {
	string str2;
	ifstream txtfile;
	txtfile.open(txtpath);

	unsigned char c;
	while (txtfile.read((char*)&c, 1)) {
		str2 += codetable[c];
	}

	/*UPDATE
	while (!txtfile.eof()) {
		char c;
		while (txtfile.get(c)) {
			str2 += codetable[c];
		}
	}
	*/

	//check length, if mod 8 != 0 , add 0 to end
	if (str2.length() % 8 != 0) {
		int j = str2.length() % 8;
		string ss;
		stringstream sout;
		while (j != 8) {
			sout << 0;
			j++;
		}
		ss = sout.str();
		str2 += ss;
	}

	//close fstream
	txtfile.close();
	return str2;
}

//generate header string using frequency table
string HuffTree::generateheader(unsigned frequency_table[256]) {
	
	string header = "";
	//first add num of unique chars info
	int uniq = numofuniq(frequency_table);
	header = header + char2binary(uniq, 2) ;	//SPACE!!!
	int i;
	for (i = 0 ; i < 256; i++) {
		if (frequency_table[i] != 0) {
			//cout << "THE  i = (WATCH OUT 40!!!)" << i << endl;
			string charbyte = char2binary((unsigned)i, 1);
			//cout << "charbyte = " << charbyte << endl;
			//cout << "frequencytable " << "at i " << i << "=" <<frequency_table[i] << endl;
			string freqbyte = char2binary(frequency_table[i], 4);
			//cout << "freqbyte=" << freqbyte << endl;
			header += charbyte;
			header += freqbyte;
		}
	}
	return header;
}

int HuffTree::numofuniq(unsigned frequency_table[256]) {
	int i = 0;
	int uniq = 0;	// num of unique chars
	for (i = 0; i < 256; i++) {
		if (frequency_table[i] != 0) {
			uniq++;
		}
	}
	return uniq;
}

//a is the char, num is the num of bytes
string HuffTree::char2binary(int a ,int num) {	
	int left = a;	//left = number/baseto
	int remain = 0;	//Remainder
	int numbit = num * 8;	//num of bits

	string store;
	/*char* store = (char*)malloc(numbit+1 * sizeof(char));
	store = (char*)calloc(numbit+1, sizeof(char));
	*/

	int i = 0;
	while (left > 0) {
		//store the remainder
		remain = left % 2;
		store += (remain+'0');
		++i;
		//do the division process
		left = left / 2;
	}
	//cout << "the i is : " << i << endl;
	//cout << "store is: " << store << endl;
	//store[i] = '\0';

	string reverse;
	/*char* reverse = (char*)malloc(numbit+1 * sizeof(char));	//reverse the order of store
	reverse = (char*)calloc(numbit+1, sizeof(char));
	*/
	int j;
	for (j = 0; j < i; ++j) {
		reverse += store[i - j - 1];
	}
	//reverse[i] = '\0';

	string total, addup;
	/*char* total = (char*)malloc(numbit+1 * sizeof(char));
	total = (char*)calloc(numbit+1, sizeof(char));	//initialize to zero memory
	char* addup = (char*)malloc((numbit - i+1) * sizeof(char));
	addup = (char*)calloc((numbit - i+1), sizeof(char));
	*/
	int abc;
	for (abc = 0; abc < numbit - i; ++abc) {
		addup += '0';
	}
	//addup[abc] = '\0';

	/*strcat(total, addup);
	strcat(total, reverse);
	total[numbit] = '\0';
	*/
	total = addup + reverse;

	//string str(total);

	if (num == 1) {
		return total;
	}else{
		relocateeightzeros(total, num);
	}
	return total;
}

void HuffTree::relocateeightzeros(string &str, int num) {	//& to make this editable

	//NEW NEW UPDATE
	int idx = 0;
	string newstr;
	if (num == 4){
		string str1 = str.substr(0, 8);
		string str2 = str.substr(8, 8);
		string str3 = str.substr(16, 8);
		string str4 = str.substr(24, 8);
		newstr = str4 + str3 + str2 + str1;
	}
	if (num == 2) {
		string str1 = str.substr(0, 8);
		string str2 = str.substr(8, 8);
		newstr = str2 + str1;
	}


	/*UPDATE
	if (str[idx] == '0' && str[idx + 1] == '0' && str[idx + 2] == '0' &&str[idx + 3] == '0' &&str[idx + 4] == '0' &&str[idx + 5] == '0' && str[idx + 6] == '0'&& str[idx + 7] == '0') {
		string strtruncate = str.substr(idx + 8);
		string eightzeros("00000000");
		str = strtruncate + eightzeros;
	}
	else {
		return;
	}
	relocateeightzeros(str);
	*/
	str = newstr;
}


HuffTree::~HuffTree() {

}
