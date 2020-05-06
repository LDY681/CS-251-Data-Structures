#include <iostream>
#include <string>
#include "expr_eval.h"

using namespace std;

int main(){
	string input;
	string earlyinput;
	expr_eval e;

	cin >> input;
	while (!cin.eof()){
		if (input.find("x") != std::string::npos){
			earlyinput = input;
			cin >> input;
			double x = input[0] - '0';
			cout << e.eval(earlyinput,x) << endl;
		}else{
			cout << e.eval(input) << endl;
		}
		cin >> input;
	}
	cout << endl;
}
