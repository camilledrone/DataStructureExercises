#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include "arbreAVL.cpp"
#include <random>

using namespace std;

void chargerArbre(AVLTree<int>& arbreAVL);

int main(int argc, char *argv[])
{
	AVLTree<int> arbreAVL;
	chargerArbre(arbreAVL);
	cout << arbreAVL;

    system("PAUSE");
    return EXIT_SUCCESS;
}

void chargerArbre(AVLTree<int>& arbreAVL)
{
	int valeurs[] = { 3, 2, 1, 4, 5, 6, 7, 16, 15, 14, 13, 12, 11, 10, 8, 9 };
	int nbValeurs = sizeof valeurs / sizeof * valeurs;
	cout << "Chargement de " << nbValeurs << " dans l'arbre binaire : 3, 2, 1, 4, 5, 6, 7, 16, 15, 14, 13, 12, 11, 10, 8, 9" << endl;
	for (int x = 0; x < nbValeurs; x++)
		arbreAVL.insert(valeurs[x]);
}
