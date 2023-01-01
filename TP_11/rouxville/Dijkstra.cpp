#include "Dijkstra.h"
#include <iostream>
using namespace std;


/*
* Constructor
* The distance of the source to itself is set to 0 and the distances to all the other vertices are set to infinite
* The parents are all null (-1)
*/

Dijkstra::Dijkstra(AdjacencyMatrix _adj, int _source, int _destination) 
{
    adj = _adj;
    source = _source;
    destination = _destination;

    cout << "Initialisation" << endl;

    int nbVertices = adj.getNumberVertices();
    vector<int> infinite(nbVertices, 100000);
    vector<int> null(nbVertices, -1);
    distanceToSource = infinite;
    parent = null;

    distanceToSource[source] = 0;
    verticesToProcess = adj.getAllVerticesWithFirstGiven(source);
}


/*
* Function to display the shortest paths between the source and the destination.
* Gives also the distance of the graphe's vertices to the source.
*/
void Dijkstra::dijkstra()
{

    int u;
    vector<vector<int>> w = adj.getGraphe();
    while (!verticesToProcess.empty()) {
        u = extractMin(w);

        list<int> neighbours = adj.getNeighbours(u);
        using Iter = std::list<int>::const_iterator;
        for (Iter it = neighbours.begin(); it != neighbours.end(); it++) {
            release(u, *it, w);
        }
    }

    //result
    cout << endl << "Les destinations a parcourir entre " << vertexToLetter(source) << " et " << vertexToLetter(destination) << " sont : ";
    findPath();

    cout << endl << "Les distances " << endl;
    for (int i = 0; i < distanceToSource.size(); i++) {
        cout << vertexToLetter(i) << " : " << distanceToSource[i] << endl;
    }

    cout << endl << "La distance totale du voyage est de " << distanceToSource[destination] << endl;
}


/*
* Given a new visited vertex (vertex 1) we look at his neighbour (vertex2) and look if the distance to the source can be updated (if the new path is shortest)
*/
void Dijkstra::release(int& vertex1, const int& vertex2, vector<vector<int>> w)
{
    cout << "Relachement de " << vertexToLetter(vertex2) << endl;
    if (distanceToSource[vertex2] > distanceToSource[vertex1] + w[vertex1][vertex2])
    {
        int previousDistance = distanceToSource[vertex2];
        int previousParent = parent[vertex2];

        distanceToSource[vertex2] = distanceToSource[vertex1] + w[vertex1][vertex2];
        parent[vertex2] = vertex1;

        cout << "d[" << vertex2 << "] = " << previousDistance << " --> " << distanceToSource[vertex2] << endl;
        cout << "p[" << vertex2 << "] = " << previousParent << " --> " << parent[vertex2] << endl;
    }
}


/*
* Extracts the nearest summit to those visited
*
* For that :
* 1) we go through the list of vertices to process
* 2) for each vertx, we get its distance to each vertex of the list of the visitied vertices
*      - if the distance strictly superior then they are neighbours
*      - if less than the smallest distance currently found then the vertex is set as the minimum
*/
int Dijkstra::extractMin(vector<vector<int>> graphe)
{
    int min;
    int shortestDistance = 100000;
    //if we haven't visited any vertex yet, we just have to take the first which is the source, thanks to the adjacency method 
    //called to fill the list of vertices to process
    if (verticesKnown.empty())
    {
        min = verticesToProcess.front();
    }

    else
    {
        using Iter = std::list<int>::const_iterator;
        for (Iter vertexToProcess = verticesToProcess.begin(); vertexToProcess != verticesToProcess.end(); vertexToProcess++) {
            for (Iter vertexVisited = verticesKnown.begin(); vertexVisited != verticesKnown.end(); vertexVisited++) {
                if (graphe[*vertexVisited][*vertexToProcess] > 0 && graphe[*vertexVisited][*vertexToProcess] < shortestDistance) {
                    min = *vertexToProcess;
                    shortestDistance = graphe[*vertexVisited][*vertexToProcess];
                }
            }
        }

    }

    verticesToProcess.remove(min);
    cout << "-------------------" << endl;
    cout << "Extraction de " << vertexToLetter(min) << endl;
    verticesKnown.push_back(min);
    return min;

}


/*
* Function to find a path from the source vertex to the destination vertex.
* The vertices visited are printed and if there is no path it prints impossible.
*
* We start from the destination vertex and we go back up to the destination through the parent vector
*/
void Dijkstra::findPath()
{
    bool pathFound = false;
    int vertex = destination;

    while (!pathFound)
    {
        if (parent[vertex] != -1)
            //if we can go to the next vertex (parent)
        {
            cout << vertexToLetter(vertex) << " <- ";
            vertex = parent[vertex];
        }

        else if (parent[vertex] == -1 && source == destination) {
            //if the destination is the same vertex as the source one but there is no path (they are not neighbours)
            cout << "\nChemin impossible !";
            return;
        }

        else if (vertex == source) {
            cout << vertexToLetter(source) << endl;
            pathFound = true;
        }

    }

}

/*
* Function for displaying vertices in letters
*/
string Dijkstra::vertexToLetter(int vertex) {
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