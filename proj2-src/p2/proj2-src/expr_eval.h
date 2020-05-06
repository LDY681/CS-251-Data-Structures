#ifndef EXPR_EVAL_H
#define EXPR_EVAL_H

#include <string>
#include "mystack.h"
#include <string>


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
	double res, rear,front = 0;
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
			valStk.push(res);

			//2nd: push the Op
			string a;
			a[0] = str[i];
			front = i + 1;
			while (!is_number(str[front])) {
				a[front - i] = str[front];
				front++;
			}
			repeatOps(a);
			opStk.push(a);
			i = front;
		}

		repeatOps("$");
		return valStk.top();
	}
}

//Case: x detected in string
double expr_eval::eval(string str , double x ) {	
	std::size_t found = str.find("x");
	str[found] = *str.end();
	*str.end() = ' ';

	double res, rear, front = 0;
	double base = 1;
	for (int i = 0; i < str.size(); i++) {
		if (!is_number(str[i]) && str[i] != ' ') {
			//1st: push the number before nonnumber Op
			rear = i - 1;
			while (is_number(str[rear])) {
				res += (str[rear] - '0')* base;
				base *= 10;
				rear--;
			}
			valStk.push(res);

			//2nd: push the Op
			string a;
			a[0] = str[i];
			front = i + 1;
			while (!is_number(str[front])) {
				a[front - i] = str[front];
				front++;
			}
			repeatOps(a);
			opStk.push(a);
			i = front;
		}

		repeatOps("$");
		return valStk.top();
	}

}


bool expr_eval::is_number(char c) {
	if (0 <= c - '0' <= 9) {
		return true;
	}
	else {
		return false;
	}
}

void expr_eval::repeatOps(string Op) {
	while (valStk.size() > 1 && (prec(Op) <= prec(opStk.top()))) {
		doOp();
	}
}

//TODO:special cases
int expr_eval::prec(string Op) {
	//+- */ sin log
	if (Op.compare("+") == 0 || Op.compare("-") == 0) {
		return 1;
	}
	else if (Op.compare("*") == 0 || Op.compare("-")) {
		return 2;
	}
	else if (Op.compare("$") == 0) {
		return 99999;
	}
	else {
		return 999;	//TODO: special cases
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
	else return 0;	//TODO: special cases
}



#endif
