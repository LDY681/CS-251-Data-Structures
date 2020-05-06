#include <iostream>
#include <string>
#include <map>
#include "graph.h"
#include <algorithm> 
#include "float.h"
#include <iomanip>
#define INFI 1000000
#include <limits.h>
#include <array>
#include <vector>



/*
	Graph class for use in Project 5.
	
	This provided code does not include any specific data structure
	for storing a graph, only a list of methods that will be called 
	from main. Based on the project handout and the lecture slides,
	select a method for storing the graph and implement it here.

*/

// Constructor for Graph 
Graph::Graph(int Vertices, int routes)
{
	//PART1 initilization
	numCities = Vertices;
	numRoutes = routes;	
	stringi = 0;

	//Initilize adjacency matrix and edge matrix
	adj = new int*[Vertices];
	edge = new double*[Vertices];
	cities = new string[Vertices];

	int i;
	for (i = 0; i < Vertices; i++) {
		adj[i] = new int[Vertices];
		edge[i] = new double[Vertices];
	}

	//Initialize visited array
	visited = new bool[Vertices];

	for (i = 0; i < Vertices; i++) {
		visited[i] = false;
	}

	//part3 arrofvecs inilization
	int count = 0;
	while (count < Vertices) {
		string city = cities[count];
		vector<string> vec;
		pair <string, vector<string>> PAIR = make_pair(city, vec);
		arrofvecs.insert(PAIR);
		count++;
	}
}

//create the graph, (string, string, double) -> (city1, city2, weight of edge)
void Graph::addRoute(string a , string b , double c ) {
	string A = a;
	string B = b;
	double C = c;
	//adj[][];

	int searchA = citysearch(A);
	if (searchA == -1) {
		cities[stringi] = a;
		searchA = stringi;
		stringi++;
	}
	int searchB = citysearch(B);
	if (searchB == -1) {
		cities[stringi] = b;
		searchB = stringi;
		stringi++;
	}
	adj[searchA][searchB] = 1;
	adj[searchB][searchA] = 1;
	edge[searchA][searchB] = c;
	edge[searchB][searchA] = c;
}

//return the index of city
int Graph::citysearch(string city) {
	if (stringi == 0) {
		//cout << "cities is empty" << endl;
		return -1;	//return -1 if empty
	}
	int i;
	for (i = 0; i < numCities; i++) {
		if (cities[i].compare(city) == 0) {	//city is found in cites
			return i;	//return index of city if found
		}
	}
	return -1;	//return -1 if not found
}


//PART1

void Graph::analyseGraph() {
	//connected components
	analyseGraph_cc();
	//bridges
	analyseGraph_bg();
}

//find connected components
void Graph::analyseGraph_cc() {
	//reinitialize visited status
	visited = new bool[numCities];
	int i;
	for (i = 0; i < numCities; i++) {
		visited[i] = false;
	}

	int node = 0;
	int numcc = 0;
	while (node < numCities) {
		if (visited[node] == false) {
			ccdfs(node);
			numcc++;
		}
		node++;
	}	
	//first cout: number of connected components
	cout << numcc << endl;
}

//Modified dfs on finding connected components
void Graph::ccdfs(int node) {
	visited[node] = true;
	int i;
	for (i = 0; i < numCities; i++) {
		if (adj[node][i] && !visited[i]) {
			//if a node has adjacent node and isnt visited
			ccdfs(i);
		}
	}
}

//find bridges
void Graph::analyseGraph_bg() {

	//New Variables 
	int *disc = new int[numCities];	//discovery time array
	int *low = new int[numCities];	//pass low value to parent
	int *parent = new int[numCities];	//parent array of node on an index

	//reinitialize visited status
	visited = new bool[numCities];
	int i;
	for (i = 0; i < numCities; i++) {
		visited[i] = false;
		parent[i] = -1;
		low[i] = -1;
		disc[i] = -1;
	}

	for (int i = 0; i < numCities; i++){
		if (visited[i] == false){
			bgdfs(i, visited, disc, low, parent);	
		}
	}

	//second cout: number of seperation edges and lists
	cout << sep.size() << endl;
	for (string &s : sep){
		cout << s << endl;
	}
}

//Modified dfs on finding bridges
void Graph::bgdfs(int node, bool visited[], int disc[], int low[], int parent[]) {
	static int time = 0;
	visited[node] = true;
	disc[node] = low[node] = ++time;

	int i;
	for (i = 0; i < numCities; i++) {
		if (adj[node][i] && !visited[i]) {	////if a node has adjacent node and isnt visited
			parent[i] = node;
			bgdfs(i, visited, disc,	 low, parent);
			low[node] = min(low[node], low[i]);
			if (low[i] > disc[node]){
				string str;
				if (cities[node] < cities[i]) {
					str = cities[node] + " " + cities[i];
				}
				else {
					str = cities[i] + " " + cities[node];
				}
				
				sep.push_back(str);
				sort(sep.begin(), sep.end());

			}
		}else if (adj[node][i] &&  i != parent[node]){	//not parent node, compare low and disc
			low[node] = min(low[node], disc[i]);
		}
	}
}

//PART2

void Graph::findCost(const string &source, const string &destination) {
	string src = source;
	string dest = destination;

}

void Graph::buildtable(string source, string dest) {
	//initialize the table map<string, node>
	map <string, node> nodelist;
	int count = 0;
	while (count < numCities) {
		struct node citynode = { 0 };
		citynode.dist = INFI;
		citynode.prev = "";
		citynode.visited = false;
		string currcity = cities[count];
		//cout << "check cities[count]: " << cities[count] << endl;
 		pair <string, node> PAIR = make_pair(currcity, citynode);
		nodelist.insert(PAIR);
		count++;
	}	
	
	//construct table
	string currnode = source;
	nodelist[source].dist = 0;
	nodelist[source].prev = "source";
	while (nodelist[dest].visited == false) {
		nodelist[currnode].visited = true;

		vector <pair <string, double>> adjlist;
		int idx = citysearch(currnode);
		int i = 0;
		while (i < numCities) {
			if (adj[idx][i] == 1) {
				pair <string, double>PAIR = make_pair(cities[i], edge[idx][i]);
				adjlist.push_back(PAIR);
			}
			i++;
		}

		for (auto&item : adjlist) {
			if ((nodelist[currnode].dist + item.second < nodelist[item.first].dist) && (nodelist[item.first].visited == false)) 
			{
				nodelist[item.first].dist = nodelist[currnode].dist + item.second;
				nodelist[item.first].prev = currnode;
			}
		
		}


		string minnode = currnode;
		double minval = INFI;
		for (auto&obj : nodelist) {
			if (obj.second.visited == false) {
				if (minval > obj.second.dist) {
					minval = obj.second.dist;
					minnode = obj.first;
				}
			}
		}
		currnode = minnode;
		//cout << minval <<  " " << minnode << endl;
	}

	
	//print path
	vector<string>vec;
	string tras = dest;
	while (tras != source) {
		//cout << tras << " ";
		vec.push_back(tras);
		tras = nodelist[tras].prev;
	}
	vec.push_back(tras);
	reverse(vec.begin(), vec.end());
	//cout << tras << endl;
	for (auto&item : vec) {
		cout << item << " ";
	}
	//find cost and print node
	cout << fixed << setprecision(2) <<nodelist[dest].dist << endl;
}

//PART3
void Graph::primMST()
{
	int *parent = new int [numCities]; // Array to store constructed MST
	int *key = new int[numCities];   // Key values used to pick minimum weight edge in cut
	bool *mstSet = new bool[numCities] ;  // To represent set of vertices not yet included in MST

	// Initialize all keys as INFINITE
	for (int i = 0; i < numCities; i++)
		key[i] = INT_MAX, mstSet[i] = false;

	// Always include first 1st vertex in MST.
	int firstctidx = citysearch(root);
	key[firstctidx] = 0;     // Make key 0 so that this vertex is picked as first vertex
	parent[firstctidx] = -1; // First node is always root of MST 

					// The MST will have V vertices
	for (int count = 0; count < numCities - 1; count++)
	{
		// Pick the minimum key vertex from the set of vertices
		// not yet included in MST
		int u = minKey(key, mstSet);

		// Add the picked vertex to the MST Set
		mstSet[u] = true;

		// Update key value and parent index of the adjacent vertices of
		// the picked vertex. Consider only those vertices which are not yet
		// included in MST
		for (int v = 0; v < numCities; v++)

			// graph[u][v] is non zero only for adjacent vertices of m
			// mstSet[v] is false for vertices not yet included in MST
			// Update the key only if graph[u][v] is smaller than key[v]
			if (edge[u][v] && mstSet[v] == false && edge[u][v] <  key[v])
				parent[v] = u, key[v] = edge[u][v];
	}

	//print the constructed MST
	//printMST(parent, numCities, edge);

	//construct a map of string vectors that contains all children
	
	//add children to parent vector
	int i = 0;
	for (i = 0; i < numCities; i++) {
		if (i != citysearch(root)){
			string par = cities[parent[i]];
			arrofvecs[par].push_back(cities[i]);
		}
	}

	//cout << "Passingpoint1" << endl;
	//sort children in alphabetical order
	for (i = 0; i < numCities; i++) {
		if (i != citysearch(root)) {
			string stri = cities[i];
			sort(arrofvecs[stri].begin(), arrofvecs[stri].end(), compareFunction());
		}
	}
	//cout << "Passingpoint2" << endl;
	eulerianTour(root);
	//cout << "Passingpoint3" << endl;
}


void Graph::eulerianTour(string node) {
	cout << node << endl;
	for (auto&obj : arrofvecs[node]) {
		eulerianTour(obj);
	}
}

//int Graph::printMST(int parent[], int n, double **edge)
//{
//	//printf("Edge   Weight\n");
//	for (int i = 0; i < numCities; i++){
//		if (i != citysearch(root)){
//			cout << cities[parent[i]] << "  " << cities[i] << "  "  << edge[i][parent[i]] << endl;
//		}
//	}
//}




int Graph::minKey(int key[], bool mstSet[])
{
	// Initialize min value
	int min = INT_MAX, min_index;

	for (int i = 0; i < numCities; i++)
		if (mstSet[i] == false && key[i] < min)
			min = key[i], min_index = i;

	return min_index;
}

string Graph::setroot(string root) {
	this->root = root;
}











