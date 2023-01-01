#pragma once
#include <vector>
#include <list>
#include <ostream>
using namespace std;

class AdjacencyMatrix
{

private:
	int numberVertices;
	int numberEdges;
	vector<vector<int>> graphe;

public:
	AdjacencyMatrix() {
		numberVertices = 0;
		numberEdges = 0;
	}

	friend ostream& operator<< (ostream& out, const AdjacencyMatrix& adjacencyMatrix)
	{
		out << "----------------------------------------------------" << endl;
		for (int i = 0; i < adjacencyMatrix.numberVertices; i++) {
			out << "\t  " << i;
		}
		out << endl;

		for (int i = 0; i < adjacencyMatrix.numberVertices; i++) {
			out << "\n" << i;
			for (int j = 0; j < adjacencyMatrix.numberVertices; j++) {
				out << "\t  " << adjacencyMatrix.graphe[i][j];
			}
		}

		out << "\n----------------------------------------------------" << endl;
		return out;
	}

	void setNumberVertices(int nbVertices);
	void addToGraphe(int vertex, int neighbour);
	vector<vector<int>> getGraphe() { return this->graphe; }
	int getNumberVertices() { return this->numberVertices; }
	list<int> getNeighbours(int vertex);

};

