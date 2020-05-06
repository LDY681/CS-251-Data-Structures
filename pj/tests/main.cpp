#include <iostream>
#include <string>
#include "graph.h"
 
using namespace std;
 

 // Part 1 : Find the connected components and the bridge
void part1(){
	//cin every input till the end
	int numCities, numRoutes;
	cin >> numCities >> numRoutes;
	//cout << "numCities: " << numCities << "numRoutes: " << numRoutes << endl;
	Graph gp(numCities, numRoutes);

	string cityA;
	string cityB;
	double weight;
	while (!cin.eof()) {
		cin >> cityA >> cityB >> weight;
		//cout << "Add " << cityA << " and " << cityB << "with weight " << weight << endl;
		gp.addRoute(cityA, cityB, weight);
	}

	//find the connected components
	gp.analyseGraph_cc();
	//cout << "connected component successful" << endl;
	gp.analyseGraph_bg();
	//cout << "seperation edges succesfful" << endl;

}

 // Part 2 :  Find a ticket using Dijkstra	(shortest path algorithm)
void part2()
{
	//cin every input till the end
	int numCities, numRoutes;
	cin >> numCities >> numRoutes;
	//cout << "numCities: " << numCities << "numRoutes: " << numRoutes << endl;
	Graph gp(numCities, numRoutes);

	string cityA;
	string cityB;
	double weight;
	int count = 0;
	while (count < numRoutes) {
		cin >> cityA >> cityB >> weight;
		//cout << "Add " << cityA << " and " << cityB << "with weight " << weight << endl;
		gp.addRoute(cityA, cityB, weight);
		count++;
	}

	
	cin >> cityA >> cityB;
	while (cityA != "END" && cityB != "END") {
		//cout << "check if input is received: " << cityA << " " << cityB << endl;
		gp.buildtable(cityA, cityB);	
		cin >> cityA >> cityB;
	}

}

 // Part 3 :Try to do a tour of all cities 
void part3()
{
	//cin every input till the end
	int numCities, numRoutes;
	cin >> numCities >> numRoutes;
	//cout << "numCities: " << numCities << "numRoutes: " << numRoutes << endl;
	Graph gp(numCities, numRoutes);

	string cityA;
	string cityB;
	double weight;
	int count = 0;
	while (count < numRoutes) {
		cin >> cityA >> cityB >> weight;
		//cout << "Add " << cityA << " and " << cityB << "with weight " << weight << endl;
		gp.addRoute(cityA, cityB, weight);
		count++;
	}
	
	string root;
	cin >> root;
	gp.root = root;
	gp.primMST();
}
 
 int main()
 {
	 double cmd;
	 cin >> cmd;

	 if(cmd == 1) part1();
	 else if(cmd == 2) part2();
	 else if(cmd == 3) part3();

	 return 0;
 }
