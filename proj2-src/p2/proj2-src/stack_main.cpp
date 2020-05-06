#include<iostream>
#include "mystack.h"
#include <string>
using namespace std;

/*cin always consider space as terminator
so cin >> mystring will only be single word
to get whole line, do getline(cin, mystring)
*/

//function is_number declaration 
bool is_number(string str);

//main
int main(){

	//confirm datatype(int, double, char or string) and call corsepsonding mystack class
	// if ii = 1, then the datatype is int
	string type;
	cin >> type;
	mystack<int> i;
	mystack<double> d;
	mystack<char> c; 
	mystack<string> s;
	int ii, dd, cc, ss = 0;
	if (type.compare("int") == 0) {
		ii = 1;
	}
	else if (type.compare("double") == 0 ) {
		dd = 1;
	}
	else if (type.compare("char") == 0) {
		cc = 1;
	}
	else{
		ss = 1;
	}

	//while loop	
	string input;

	if (ii == 1){
		cin >> input;
		while (!cin.eof()) {	
			if (!is_number(input)) {	//if its a command
				if (input.compare("push") == 0) {
					int num;
					cin >> num;
					i.push(num);
				}else if (input.compare("top") == 0) {
					cout << i.top() << "\n";
				}else if (input.compare("pop") == 0) {
					cout << i.pop() << "\n";
				}else if (input.compare("empty") == 0) {
					cout << i.empty() << "\n";
				}else if (input.compare("size") == 0) {
					cout << i.size() << "\n";
				}else { ; }
			}
			cin >> input;
		}
	}
	else if (dd == 1) {
		cin >> input;
		while (!cin.eof()) {
			if (!is_number(input)) {	//if its a command
				if (input.compare("push") == 0) {
					double num;
					cin >> num;
					d.push(num);
				}else if (input.compare("top") == 0) {
					cout << d.top() << "\n";
				}else if (input.compare("pop") == 0) {
					cout << d.pop() << "\n";
				}else if (input.compare("empty") == 0) {
					cout << d.empty() << "\n";
				}else if (input.compare("size") == 0) {
					cout << d.size() << "\n";
				}else { ; }
			}
			cin >> input;
		}
	}
	else if (cc == 1) {
		cin >> input;
		while (!cin.eof()) {
			if (!is_number(input)) {	//if its a command
				if (input.compare("push") == 0) {
					char num;
					cin >> num;
					c.push(num);
				}else if (input.compare("top") == 0) {
					cout << c.top() << "\n";
				}else if (input.compare("pop") == 0) {
					cout << c.pop() << "\n";
				}else if (input.compare("empty") == 0) {
					cout << c.empty() << "\n";
				}else if (input.compare("size") == 0) {
					cout << c.size() << "\n";
				}else { ; }
			}
			cin >> input;
		}
	}
	else if (ss == 1) {
		cin >> input;
		while (!cin.eof()) {
			if (!is_number(input)) {	//if its a command
				if (input.compare("push") == 0) {
					string num;
					cin >> num;
					s.push(num);
				}else if (input.compare("top") == 0) {
					cout << s.top() << "\n";
				}else if (input.compare("pop") == 0) {
					cout << s.pop() << "\n";
				}else if (input.compare("empty") == 0) {
					cout << s.empty() << "\n";
				}else if (input.compare("size") == 0) {
					cout << s.size() << "\n";
				}else { ; }
			}
			cin >> input;
		}
	}
	cout << "\n";
}

bool is_number(string str){
	for (int i = 0; i < (str.length() - 1); i++) {
		if ((int)str[i] < 10) {
			return true;
		}
		else {
			return false;
		}
	}
}
