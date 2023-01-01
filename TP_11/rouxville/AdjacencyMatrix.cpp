#include "AdjacencyMatrix.h"


void AdjacencyMatrix::setNumberVertices(int nbVertices)
{
	this->numberVertices = nbVertices;

	vector<int> zero = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
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
void AdjacencyMatrix::addToGraphe(int vertex, int neighbour, int edgeWeight) {
	this->graphe[vertex][neighbour] = edgeWeight;
	this->numberEdges++;
}


/*
* return the list of a vertex's neighbours
*/
list<int> AdjacencyMatrix::getNeighbours(int vertex) {
	list<int> neighbours;
	for (int i = 0; i < graphe.size(); i++) {
		if (graphe[vertex][i] > 0) {
			neighbours.push_back(i);
		}
	}
	return neighbours;
}


/*
* Return the list of the graphe's vertices, with a given vertex in the first position (ofr dijkstra)
*/
list<int> AdjacencyMatrix::getAllVerticesWithFirstGiven(int vertex) {
	list<int> vertices;
	vertices.push_back(vertex);
	for (int i = 0; i < graphe.size(); i++) {
		if (i != vertex) {
			vertices.push_back(i);
		}
	}
	return vertices;
}


/*
* Function for displaying vertices in letters
*/
string AdjacencyMatrix::vertexToLetter(int vertex) {
	switch (vertex)
	{
	case 0:
		return "A";
	case 1:
		return "B";
	case 2:
		return "C";
	case 3:
		return "D";
	case 4:
		return "E";
	case 5:
		return "F";
	case 6:
		return "G";
	case 7:
		return "H";
	case 8:
		return "I";
	case 9:
		return "J";
	case 10:
		return "K";

	default:
		return " ";
	}
}