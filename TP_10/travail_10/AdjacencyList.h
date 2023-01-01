#pragma once
#include <vector>
#include <ostream>
#include <list>
using namespace std;

class AdjacencyList
{

private:
	int numberVertices;
	int numberEdges;
	vector<list<int>> graphe;

public:
	AdjacencyList() {
		numberVertices = 0;
		numberEdges = 0;
	}

	friend ostream& operator<< (ostream& out, AdjacencyList& adjacencyList)
	{
		out << "----------------------------------------------------" << endl;
		out << "Source\tDestinations" << endl;

		for (int i = 0; i < adjacencyList.graphe.size(); i++) {

			int vertex = adjacencyList.graphe[i].front();
			out << vertex << "\t";
			adjacencyList.graphe[i].pop_front();

			using Iter = std::list<int>::const_iterator; //utilisation d'un iterateur constant pour parcourir la liste 
			for (Iter it = adjacencyList.graphe[i].begin(); it != adjacencyList.graphe[i].end(); it++) {
				out << *it << ", ";
			}

			adjacencyList.graphe[i].push_front(vertex);
			out << endl;
		}

		out << "\n----------------------------------------------------" << endl;
		return out;
	}

	void setNumberVertices(int nbVertices) { this->numberVertices = nbVertices; }
	void addToGraphe(int vertex, int neighbour);
	vector<list<int>> getGraphe() { return this->graphe; }
	int getNumberVertices() { return this->numberVertices;}
	list<int> getNeighbours(int vertex);
};

