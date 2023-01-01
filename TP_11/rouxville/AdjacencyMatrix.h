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

	static string vertexToLetter(int vertex);

public:
	AdjacencyMatrix() {
		numberVertices = 0;
		numberEdges = 0;
	}

	~AdjacencyMatrix() {};
	
	friend ostream& operator<< (ostream& out, const AdjacencyMatrix& adjacencyMatrix)
	{
		out << "----------------------------------------------------" << endl;
		for (int i = 0; i < adjacencyMatrix.numberVertices; i++) {
			out << "\t  " << vertexToLetter(i);
		}
		out << endl;

		for (int i = 0; i < adjacencyMatrix.numberVertices; i++) {
			out << "\n" << vertexToLetter(i);
			for (int j = 0; j < adjacencyMatrix.numberVertices; j++) {
				out << "\t  " << adjacencyMatrix.graphe[i][j];
			}
		}

		out << "\n----------------------------------------------------" << endl;
		return out;
	}

	void setNumberVertices(int nbVertices);
	void addToGraphe(int vertex, int neighbour, int edgeWeight);
	vector<vector<int>> getGraphe() { return this->graphe; }
	int getNumberVertices() { return this->numberVertices; }
	list<int> getNeighbours(int vertex);
	list<int> getAllVerticesWithFirstGiven(int vertex);

};

