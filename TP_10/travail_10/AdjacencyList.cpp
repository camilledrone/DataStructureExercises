#include "AdjacencyList.h"


/*
* add a neighbour to the graphe of the adjacency list
* if the vertex is already in the graphe we just have to add the neighbour
* if not we have to add a list to the graphe
*/
void AdjacencyList::addToGraphe(int vertex, int neighbour) {
    bool isInList = false;

    for (int i = 0; i < graphe.size(); i++) {
        if (graphe[i].front() == vertex) {
            isInList = true;
            graphe[i].push_back(neighbour);
            numberEdges++;
        }
    }

    if (!isInList)
    {
        graphe.push_back({ vertex, neighbour });
        numberEdges++;
    }
}

/*
* return the list of a vertex's neighbours
*/
list<int> AdjacencyList::getNeighbours(int vertex) {
    list<int> neighbours;
    for (int i = 0; i < graphe.size(); i++) {
        if (graphe[i].front() == vertex) {
            neighbours = graphe[i];
            neighbours.pop_front(); //we delete the the first element, which is just the vertex
            return neighbours;
        }
    }
}