#ifndef EXPR_EVAL_H
#define EXPR_EVAL_H

#include <string>
#include "mystack.h"
#include <string>
#include <math.h>

using namespace std;

class expr_eval{
  private:
        // Declare which ever necessary variables and methods
	  mystack<string> opStk;	//stack of operations
	  mystack<double> valStk;	//stack of double

  public:
	  expr_eval() {}
	  //eval and isnumber
	  	double eval(string str);
        	double eval(string str, double x);
		bool is_number(char c);

		//repeatop and prec
		void repeatOps(string Op);	//repeat operations
		int prec(string Op);	//return the prec of a operater

		//doop and lowop
		//when prec(refop) << prec(top) do op
		void doOp();	//do operation
		double lowOp(double x, double y, string op);	//low level two number operation in doOp
};

//Potential Errors: is_number and !is_number cases are written together
//Case:no x detected in string
double expr_eval::eval(string str ) {	//Dont forget expr_eval::
	double res = 0;
	int rear, front = 0;
	double base = 1;

	for (int i = 0; i < str.size(); i++) {
		if ( !is_number(str[i]) ) {
			//1st: push the number before nonnumber Op
			rear = i - 1;
			while (is_number(str[rear])) {
				res += (str[rear] - '0')* base;
				base *= 10;
				rear--;
			}
			if ( res != 0){
				valStk.push(res);
			}

			//reset result and base
			res = 0;
			base = 1;

			//2nd: push the Op
			front = i + 1;
			while ( !is_number(str[front]) && str[i] != ')' ) {	
				if ( (str[i] <= '0' || str[i] >= 'z') && str[i+1] == '(' ){
					break;
				}
				front++;
			}
			string a = str.substr(i,front-i);
			repeatOps(a);
			opStk.push(a);
			if (a.compare(")") == 0){
				opStk.pop();
			}
		}

	}

	//special case at the end of string
	if (str[str.size()-1] != ')'){
		rear = str.size() - 1;
		while (is_number(str[rear])) {
			res += (str[rear] - '0')* base;
			base *= 10;
			rear--;
		}
		valStk.push(res);

		repeatOps("$");
		double ret = valStk.top();
		valStk.pop();
		return ret;
	}
	double ret = valStk.top();
	valStk.pop();
	return ret;

}

//Case: x detected in string
double expr_eval::eval(string str , double x ) {	
	std::size_t found = str.find("x");
	char xx = x + '0';
	str[found] = xx;

	double res = 0;
	int rear, front = 0;
	double base = 1;

	for (int i = 0; i < str.size(); i++) {
		if ( !is_number(str[i]) ) {
			//1st: push the number before nonnumber Op
			rear = i - 1;
			while (is_number(str[rear])) {
				res += (str[rear] - '0')* base;
				base *= 10;
				rear--;
			}
			if ( res != 0){
				valStk.push(res);
			}

			//reset result and base
			res = 0;
			base = 1;

			//2nd: push the Op
			front = i + 1;
			while ( !is_number(str[front]) && str[i] != ')' ) {	
				if ( (str[i] <= '0' || str[i] >= 'z') && str[i+1] == '(' ){
					break;
				}
				front++;
			}
			string a = str.substr(i,front-i);
			
			if ( !(a.compare("in(")== 0 || a.compare("n(") == 0 || (a.compare("(")==0 && str[i-1] == 'n') || a.compare("og(")== 0 || a.compare("g(") == 0 || (a.compare("(")==0 && str[i-1] == 'g')) ){
				repeatOps(a);
				opStk.push(a);				
			}


			if (a.compare(")") == 0){
				opStk.pop();
			}
		}

	}

	
	//special case at the end of string
	if (str[str.size()-1] != ')'){
		rear = str.size() - 1;
		while (is_number(str[rear])) {
			res += (str[rear] - '0')* base;
			base *= 10;
			rear--;
		}
		valStk.push(res);

		repeatOps("$");
		double ret = valStk.top();
		valStk.pop();
		return ret;
	}
	double ret = valStk.top();
	valStk.pop();
	return ret;
}


bool expr_eval::is_number(char c) {
	if (c - '0' >= 0 && c - '0' <= 9) {
		return true;
	}
	else {
		return false;
	}
}

void expr_eval::repeatOps(string Op) {
	if (Op.compare(")") == 0 && opStk.top().find("(") != std::string::npos){	//if we find last op as (
		if ( opStk.top().compare("(") == 0){	//if its ()
			opStk.pop();	
		}else{	 //if its trig()
			if (opStk.top().compare("sin(") == 0){	//if its sin()
				double x = valStk.pop();
				double res = sin(x *M_PI/180);
				valStk.push(res);
				opStk.pop();
			}
			if (opStk.top().compare("log(") == 0){	//if its sin()
				double x = valStk.pop();
				double res = log10(x);
				valStk.push(res);
				opStk.pop();
			}						
		}
		return;
	}
	while  ( (valStk.size() > 1 && prec(Op) <= prec(opStk.top()) && opStk.top().compare("(")!= 0 && Op.compare("(")!= 0 ) || (valStk.size() > 1 && Op.compare("$") == 0) ) {
		doOp();
	}
	if (Op.compare(")") == 0 && opStk.top().find("(") != std::string::npos){	//if we find last op as (
		if ( opStk.top().compare("(") == 0){	//if its ()
			opStk.pop();	
		}else{	 //if its trig()
			if (opStk.top().compare("sin(") == 0){	//if its sin()
				double x = valStk.pop();
				double res = sin(x *M_PI/180);
				valStk.push(res);
				opStk.pop();
			}
			if (opStk.top().compare("log(") == 0){	//if its sin()
				double x = valStk.pop();
				double res = log10(x);
				valStk.push(res);
				opStk.pop();
			}						
		}
		return;
	}

}

//TODO:special cases
int expr_eval::prec(string Op) {
	//+- */ sin log
	if (Op.compare("+") == 0 || Op.compare("-") == 0) {
		return 1;
	}
	else if (Op.compare("*") == 0 || Op.compare("/") == 0) {
		return 2;
	}
	else if (Op.compare("^") == 0){
		return 3;
	}
	else if (Op.compare("$") == 0) {
		return 99999;
	}
	else {
		return 0;	//TODO: special cases
	}
}

void expr_eval::doOp() {
	double x = valStk.pop();
	double y = valStk.pop();
	string op = opStk.pop();
	double yopx = lowOp(x, y, op);
	valStk.push(yopx);
}

//TODO: special cases
double expr_eval::lowOp(double x, double y, string op) {
	if (op.compare("+") == 0) return y + x;
	else if (op.compare("-") == 0) return y - x;
	else if (op.compare("*") == 0) return y * x;
	else if (op.compare("/") == 0) return y / x;
	else if (op.compare("^") == 0) return pow(y,x);
	else return 0;	//TODO: special cases
}



#endif
