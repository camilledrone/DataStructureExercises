#include <iostream>
#include <fstream>
#include "AdjacencyMatrix.h"
#include "Dijkstra.h"
using namespace std;

template <class T>
void loadGraphe(T& adj);


int main()
{

    cout << "BIENVENUE DANS LES CHRONIQUES DE ROUXVILLE !" << endl << endl;

    cout << "CHARGEMENT DE LA CARTE DE KARAMEICOS : " << endl; 
    AdjacencyMatrix* carte = new AdjacencyMatrix();
    loadGraphe<AdjacencyMatrix>(*carte);
    cout << *carte << endl;

    cout << endl << "RECHERCHE DU MEILLEUR CHEMIN ENTRE ROUXVILLE ET SULESCU : " << endl;
    Dijkstra* dijkstra = new Dijkstra(*carte, 0, 10);
    dijkstra->dijkstra();

    delete dijkstra;
    delete carte;
}


/*
* Load a graphe from a file to a graphe structure (matrix of adjacency)
*/
template <class T>
void loadGraphe(T& adj)
{
    ifstream in("voyage.dat");

    int nbVertices;
    in >> nbVertices;
    adj.setNumberVertices(nbVertices);

    int vertex, neighbour, edgeWeight;
    while (in >> vertex >> neighbour >> edgeWeight) //we read while we are not at the end
    {
        adj.addToGraphe(vertex, neighbour, edgeWeight); //function defined in the class AdjacencyList and AdjacencyMatrix
    }
    in.close();

}
