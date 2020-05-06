/**
 *  CS251 - Spring 2018: Project 1
 */

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

void printDash(int column);

int main(int argc, char** argv)
{
	
	/*You don't need the names of input and output files, as the command 
	program < input-test1.txt > output-test1.txt
	redirects the content of given file to your input stream and redirects your output to the given file. For you	
	that means, you can just use cin/cout to read/write and then use the above command to redirect to files.
	*/
	
	int column;
	cin >> column;
	
	int num;

	int count = 0;	// if count = column-1, we dont print | at end
	printDash(column);
	while (!cin.eof() ){
		cin >> num;

		if (count == column -1){	//last num in row case, dont forget to printDash afterward
			if ( num < 10){
				cout << "  " << num << "\r\n";
				count = 0;
				printDash(column);
			}else if( num < 100){
				cout << " " << num << "\r\n";
				count = 0;
				printDash(column);
			}else{
				cout << num << "\r\n";
				count = 0;
				printDash(column);
			}
		}else{	//normal case
			if (num < 10){
				cout << "  " << num << " | " ;
				count ++;
			}else if( num < 100){
				cout <<  " " << num << " | " ;
				count++;
			}else{
				cout << num << " | " ;
				count++;
			}
		}	//end of normal case
	}	//end of while !eof
    return 0;
}

void printDash(int column){
	int numofDash = 6*column -3;
	int i;
	for (i = 0; i < numofDash - 1; i++){
		cout << "-" ;	//Dont forget "" between dash
	}
	cout << "-" << "\r\n";
	//cout << endl;
}




    /* Use input/output using C++ like notation would use "cin" and "cout" to read/write to stdin/stdout */

    /* ------------------------------- */
    /* process inputs and write output */
    /* ------------------------------- */

	/*
	string filename = "";
	cout << "Enter the name of file you wanna to sort:";
	cin >> filename;
	

	ifstream inFile;
	ofstream outFile;
	inFile.open("input1.txt");
	outFile.open("myoutput1.txt");

	//check for error
	if ( inFile.fail() || outFile.fail() ){
		cerr << "Error opening file" << endl;
		exit(1);
	}
	
	//read file part
	int column;
       	inFile >> column;
	int numofdash = 6*column - 3;

	char c;
	char array[1000];
	int count = 0;
	while (!inFile.eof()){
		int numofint
		inFile >> c;
		array[count] = c;
		count++;
	}
		array[count] = '\0';
	
	inFile.close();

	count = 0;
	while (array[count] != '\0'){
		int countofcol = 0;
		while ( countofcol < column){

			//Draw the ------line
			for (int i = 0; i < numofdash -1; i++){
				outFile << - ;
			}
			outFile << - << endl;
			
			//assign numbers


			
		}
		
	}
	outFile.close();
	*/

	

    /* Exit the program */
