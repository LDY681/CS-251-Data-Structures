#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

struct node{
	double dist;	//distance
	string prev;	//index of previous node 
	bool visited;
};

struct compareFunction {
	bool operator()(const string a, string b) const {
		return a < b;
	}
};

class Graph
{
private:
	int numCities;
	int numRoutes;
	//string *cities;
	double weight;

	//Part1
	//New created variables
	int **adj;	//the adjacent matrix 
	double **edge; //the matrix with weight of edge
	bool *visited;	//the value of visit on an index
	string *cities;	//the name of city on an index
	int stringi;	//the index of new city in string cities
	vector<string> sep;	//list of seperation edges;
	
	//PART2
	//new created varibles
	//map <pair<string, node>> initial;

	//PART3
	
	map<string, vector<string>> arrofvecs;

public:
	string root;
	Graph(int, int);
	// Create the graph
	void addRoute(string a, string b, double c);

	//part 1: Find the connected components and the bridges
	void analyseGraph();
	//New added to part1
	void analyseGraph_cc();
	void ccdfs(int node);
	void analyseGraph_bg();
	void bgdfs(int node, bool visited[], int disc[], int low[], int parent[]);

	// Part 2: Find a ticket using Dijkstra	
	void findCost(const string &source, const string &destination);
	//new added to part2
	void buildtable(string source, string dest);



	// Part 3: Try to do a tour of all cities
	void eulerianTour(string node);  // NOTE : If necessary, you can change the parameters to this function.

	int citysearch(string city);//find out if city is already in string cities, return -2 if empty string, -1 if not found, return index of city if found

	void MST();
	//int printMST(int parent[], int n, double **edge);
	int minKey(int key[], bool mstSet[]);


};

#endif
