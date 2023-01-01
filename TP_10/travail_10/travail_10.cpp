#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include "AdjacencyMatrix.h"
#include "AdjacencyList.h"
#include <queue>
using namespace std;

template <class T>
void loadGraphe(T& adj);

template <class T>
void widthTrack(T& adj, int sourceVertex, vector<int>& color, vector<int>& distanceToSourceVertex, vector<int>& parent);

template <class T>
void printWidthTrack(T& adj, vector<int>& color, vector<int>& distanceToSourceVertex, vector<int>& parent);

void findPath(int sourceVertex, int destinationVertex, vector<int>& parent);

int main()
{
    //////////////////////////////////
    // Adjacency List 
    //////////////////////////////////
    cout << "//////////////////////////////////" << endl;
    cout << "Adjacency List " << endl;
    cout << "//////////////////////////////////" << endl;

    // Section #1
    cout << "\nSection #1 Chargement de la liste d'adjacence" << endl;
    cout <<  endl;
    AdjacencyList* adjlist = new AdjacencyList();
    loadGraphe<AdjacencyList>(*adjlist);
    cout << *adjlist << endl;


    // Section #3
    cout << "Section #3 Parcours en Largeur" << endl;
    cout << endl;
    int sourceVertex;
    cout << "Choisir le sommet source (0-" << (adjlist->getNumberVertices() - 1) << ") : ";
    cin >> sourceVertex;


    // Section #4
    cout << "\nSection #4 Affichage" << endl;
    cout << endl;
    vector<int> color; //white (0) , grey (1), black (2)
    vector<int> distanceToSourceVertex; //-1 is infinite
    vector<int> parent;//-1 is NULL
    widthTrack<AdjacencyList>(*adjlist, sourceVertex, color, distanceToSourceVertex, parent);
    printWidthTrack<AdjacencyList>(*adjlist, color, distanceToSourceVertex, parent);


    // Section #5
    cout << "\nSection #5 Question - Afficher le chemin" << endl;
    cout << endl;
    int destinationVertex;
    cout << "Choisir le sommet de destination (0-" << (adjlist->getNumberVertices() - 1) << ") : ";
    cin >> destinationVertex;
    findPath(sourceVertex, destinationVertex, parent);



    //////////////////////////////////
    // Adjacency Matrix 
    //////////////////////////////////
    cout << "\n//////////////////////////////////" << endl;
    cout << "Adjacency Matrix " << endl;
    cout << "//////////////////////////////////" << endl;

    // Section #1
    cout << "\nSection #1 Chargement de la matrice d'adjacence" << endl;
    cout << endl;
    AdjacencyMatrix* adjmatrix = new AdjacencyMatrix();
    loadGraphe<AdjacencyMatrix>(*adjmatrix);
    cout << *adjmatrix << endl;

    // Section #3
    cout << "Section #3 Parcours en Largeur" << endl;
    cout << endl;
    int sourceVertex2;
    cout << "Choisir le sommet source (0-" << (adjmatrix->getNumberVertices() - 1) << ") : ";
    cin >> sourceVertex2;

    // Section #4
    cout << "\NSection #4 Affichage" << endl;
    cout << endl;
    vector<int> color2; //white (0) , grey (1), black (2)
    vector<int> distanceToSourceVertex2; //-1 is infinite
    vector<int> parent2; //-1 is NULL
    widthTrack<AdjacencyMatrix>(*adjmatrix, sourceVertex2, color2, distanceToSourceVertex2, parent2);
    printWidthTrack<AdjacencyMatrix>(*adjmatrix, color2, distanceToSourceVertex2, parent2);

    // Section #5
    cout << "\nSection #5 Question - Afficher le chemin" << endl;
    cout << endl;
    int destinationVertex2;
    cout << "Choisir le sommet de destination (0-" << (adjmatrix->getNumberVertices() - 1) << ") : ";
    cin >> destinationVertex2;
    findPath(sourceVertex2, destinationVertex2, parent2);

}


/*
* Load a graphe from a file to a graphe structure (list or matrix of adjacency)
* The user can choose between the file 1 or 2
*/
template <class T>
void loadGraphe(T& adj)
{
    string nameFile;
    cout << "Entrer le numero du fichier de donnees (1 ou 2) : ";
    cin >> nameFile;
    nameFile.append(".dat");
    ifstream in(nameFile);

    int nbVertices;
    in >> nbVertices;
    adj.setNumberVertices(nbVertices);

    int vertex, neighbour;
    while (in >> vertex >> neighbour) //we read while we are not at the end
    {
        adj.addToGraphe(vertex, neighbour); //function defined in the class AdjacencyList and AdjacencyMatrix
    }
    in.close();

}


/*
* Function to calculate the distance (the smallest number of arcs) between a source vertex and all the vertices accessible from this vertex
* To keep track of the progress, we coloured summits visited:
*   - White = 0 = not visited
*   - Grey = 1 = visited but not chosen (in treatment)
*   - Black = 2 = chosen
*/
template <class T>
void widthTrack(T& adj, int sourceVertex, vector<int>& color, vector<int>& distanceToSourceVertex, vector<int>& parent)
{
    int nbVertices = adj.getNumberVertices();
    vector<int> zero(nbVertices, 0);
    vector<int> infinite(nbVertices, -1);
    color = zero;
    distanceToSourceVertex = infinite;
    parent = infinite;

    color[sourceVertex] = 1;
    distanceToSourceVertex[sourceVertex] = 0;

    queue<int> greyVertices;
    greyVertices.push(sourceVertex);
    while (!greyVertices.empty()) {
        int vertex = greyVertices.front();

        list<int> neighbours = adj.getNeighbours(vertex);
        using Iter = std::list<int>::const_iterator; 
        for (Iter it = neighbours.begin(); it != neighbours.end(); it++) {
            if (color[*it] == 0) {
                color[*it] = 1;
                distanceToSourceVertex[*it] = distanceToSourceVertex[vertex] + 1;
                parent[*it] = vertex;
                greyVertices.push(*it);
            }
        }

        greyVertices.pop();
        color[vertex] = 2;
    }

}

/*
* print the results of the wisth track
*/
template <class T>
void printWidthTrack(T& adj, vector<int>& color, vector<int>& distanceToSourceVertex, vector<int>& parent)
{
    cout << "----------------------------------------------------" << endl;
    cout << "SOMMET\t\tCOULEUR\t\tDISTANCE\tPARENT" << endl;

    int nbVertices = adj.getNumberVertices();
    for (int i = 0; i < nbVertices; i++) {
        cout << i << "\t\t" << color[i] << "\t\t" << distanceToSourceVertex[i] << "\t\t" << parent[i] << endl;
    }

    cout << "----------------------------------------------------" << endl;
    cout << "(Note : -1 --> infini ou NULL)" << endl;
}


/*
* Function to find a path from a source vertex to a destination vertex.
* The vertices visited are printed and if there is no path it prints impossible.
* 
* We start from the destination vertex and we go back up to the destination through the parent vector
*/
void findPath(int sourceVertex, int destinationVertex, vector<int>& parent)
{
    bool pathFound = false;
    int vertex = destinationVertex;
    cout << "CHEMIN : " ;
    string path = to_string(vertex);
    
    while (!pathFound)
    {
        if (parent[vertex] != -1)
            //if we can go to the next vertex (parent)
        {
            cout  << vertex << " <- ";
            vertex = parent[vertex];
        }

        else if (parent[vertex] == -1 && sourceVertex == destinationVertex) {
            //if the destination is the same vertex as the source one but there is no path (they are not neighbours)
            cout << "\nChemin impossible !";
            return;
        }

        else if (vertex == sourceVertex) {
            cout << sourceVertex << endl;
            pathFound = true;
            return;
        }       

    }
}