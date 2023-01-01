#include "AdjacencyMatrix.h"


void AdjacencyMatrix::setNumberVertices(int nbVertices) 
{ 
	this->numberVertices = nbVertices;

	vector<int> zero = { 0, 0, 0, 0, 0, 0 };
	while (this->graphe.size() != this->numberVertices) 
	{
		graphe.push_back(zero);
	}
}

/*
	* add a neighbour to the adjacency list
	* if the vertex is already in the graphe we just have to add the neighbour
	* if not we have to add a list to the graphe
	*/
void AdjacencyMatrix::addToGraphe(int vertex, int neighbour) {
	this->graphe[vertex][neighbour] = 1;
	this->numberEdges++;
}


/*
* return the list of a vertex's neighbours
*/
list<int> AdjacencyMatrix::getNeighbours(int vertex) {
	list<int> neighbours;
	for (int i = 0; i < graphe.size(); i++) {
		if (graphe[vertex][i] == 1) {
			neighbours.push_back(i);
		}
	}
	return neighbours;
}