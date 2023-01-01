#pragma once
#include <vector>
#include <list>
#include "AdjacencyMatrix.h"
using namespace std;

class Dijkstra
{

private :
	
	AdjacencyMatrix adj;
	int source;
	int destination;
	vector<int> distanceToSource;
	vector<int> parent;
	list<int> verticesKnown;
	list<int> verticesToProcess;

	void release(int& vertice1, const int& vertice2, vector<vector<int>> w);
	int extractMin( vector<vector<int>> graphe);
	void findPath();

	string vertexToLetter(int vertex);


public: 

	Dijkstra(AdjacencyMatrix _adj, int _source, int _destination);
	~Dijkstra() {}

	void dijkstra();
};

