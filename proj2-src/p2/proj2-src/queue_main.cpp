#include<iostream>
#include "myqueue.h"
#include <string>
using namespace std;

//function is_number declaration 
bool is_number(string str);

//main
int main(){

	//confirm datatype(int, double, char or string) and call corsepsonding mystack class
	// if ii = 1, then the datatype is int
	string type;
	cin >> type;
	myqueue<int> i;
	myqueue<double> d;
	myqueue<char> c; 
	myqueue<string> s;
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


	/*	void enqueue(T x);
	T front();
	T dequeue();
	bool empty();
	int size();
	*/
	//while loop	
	string input;

	if (ii == 1){
		cin >> input;
		while (!cin.eof()) {	
			if (!is_number(input)) {	//if its a command
				if (input.compare("enqueue") == 0) {
					int num;
					cin >> num;
					i.enqueue(num);
				}else if (input.compare("front") == 0) {
					cout << i.front() << "\n";
				}else if (input.compare("dequeue") == 0) {
					cout << i.dequeue() << "\n";
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
				if (input.compare("enqueue") == 0) {
					double num;
					cin >> num;
					d.enqueue(num);
				}else if (input.compare("front") == 0) {
					cout << d.front() << "\n";
				}else if (input.compare("dequeue") == 0) {
					cout << d.dequeue() << "\n";
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
				if (input.compare("enqueue") == 0) {
					char num;
					cin >> num;
					c.enqueue(num);
				}else if (input.compare("front") == 0) {
					cout << c.front() << "\n";
				}else if (input.compare("dequeue") == 0) {
					cout << c.dequeue() << "\n";
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
				if (input.compare("enqueue") == 0) {
					string num;
					cin >> num;
					s.enqueue(num);
				}else if (input.compare("front") == 0) {
					cout << s.front() << "\n";
				}else if (input.compare("dequeue") == 0) {
					cout << s.dequeue() << "\n";
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
