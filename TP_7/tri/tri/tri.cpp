#include <iostream>
#include <algorithm>
#include "algorithme.cpp"
#include <stdlib.h>
#include <time.h>  
#include <string>
#include <stdio.h>
#include <windows.h>
#include <vector>
#include <cmath>
using namespace std;

void genererTableauTrie(int tab[], int taille);
void genererTableauTrieDecroissant(int tab[], int taille);
void genererTableauAleatoire(int tab[], int taille);
int faireTri(int numero, int tab[], int taille, int typeTableau);
void imprimerResultats(double resultats[3][6], int taille);
void compare(int tab[], int taille, double resultats[3][6]);


int main()
{
	double resultats[3][6]; // tableau pour stocker les resultats des temps dexecution
	
	int valeurs_5[5];
	//compare(valeurs_5, 5, resultats);
	//imprimerResultats(resultats, 5);

	int valeurs_10[10];
	//compare(valeurs_10, 10, resultats);
	//imprimerResultats(resultats, 10);

	int valeurs_15[15];
	//compare(valeurs_15, 15, resultats);
	//imprimerResultats(resultats,15);

	int valeurs_20[20];
	//compare(valeurs_20, 20, resultats);
	//imprimerResultats(resultats, 20);

	int valeurs_25[25];
	//compare(valeurs_25, 25, resultats);
	//imprimerResultats(resultats, 25);

	int valeurs_30[30];
	//compare(valeurs_30, 30, resultats);
	//imprimerResultats(resultats, 30);

	int valeurs_50[50];
	//compare(valeurs_50, 50, resultats);
	//imprimerResultats(resultats, 50);

	int valeurs_100[100];
	//compare(valeurs_100, 100, resultats);
	//imprimerResultats(resultats, 100);

	int valeurs_1000[1000];
	compare(valeurs_1000, 1000, resultats);
	imprimerResultats(resultats, 1000);


}


/*
* Rempli le tableau donne en parametre de taille n avec les n premiers entiers impairs
*/
void genererTableauTrie(int tab[], int taille)
{
	for (int i = 0; i < taille; i++) {
		tab[i] = 2*i + 1;
	}
}


/*
* Rempli le tableau donne en parametre de taille n avec les n premiers entiers impairs dans un ordre decroissant
*/
void genererTableauTrieDecroissant(int tab[], int taille)
{
	for (int i = 0; i < taille; i++) {
		tab[i] = taille - i;
	}
}

/*
* Rempli le tableau donne en parametre de taille N avec N entiers aleatoires entre 1 et N
*/
void genererTableauAleatoire(int tab[], int taille)
{
	srand(time(NULL));
	for (int i = 0; i < taille; i++) {
		tab[i] = rand() % taille+ 1;;
	}
}


/*
* effectue un tri pour un tableau d'une taille donnee pour un algorithme demande
* on genere les valeurs du tableau selon le parametre typeTableau puis on effectue le tri selon le parametre numero
*/
int faireTri(int numero, int tab[], int taille, int typeTableau)
{
	//generer le tableau
	switch (typeTableau)
	{
	case 0:	
		genererTableauTrie(tab, taille);
		break;
	case 1:	
		genererTableauTrieDecroissant(tab, taille);
		break;
	case 2:	
		genererTableauAleatoire(tab, taille);
		break;
	}
	
	//faire le tri sur le tableau genere
	LARGE_INTEGER freq, depart, fin;
	float duree;
	switch (numero)
	{
	case 0:	 //Tri Bulles

		QueryPerformanceFrequency(&freq); // Obtient frequence
		QueryPerformanceCounter(&depart);

		triBulles(tab, taille);

		QueryPerformanceCounter(&fin);
		duree = ((fin.QuadPart - depart.QuadPart) / (float)freq.QuadPart) * 1000000000;
		break;

	case 1: //Tri Selection
		
		QueryPerformanceFrequency(&freq); // Obtient frequence
		QueryPerformanceCounter(&depart);

		triSelection(tab, taille);

		QueryPerformanceCounter(&fin);
		//duree = ((fin.QuadPart - depart.QuadPart) / (double)freq.QuadPart) * 1000000000L;
		duree = ((fin.QuadPart - depart.QuadPart) / (float)freq.QuadPart) * 1000000000L;
		duree = ceil(duree * 100) / 100;
		break;

	case 2: //Tri Insertion

		QueryPerformanceFrequency(&freq); // Obtient frequence
		QueryPerformanceCounter(&depart);

		triInsertion(tab, taille);

		QueryPerformanceCounter(&fin);
		duree = ((fin.QuadPart - depart.QuadPart) / (float)freq.QuadPart) * 1000000000L;
		duree = ceil(duree * 100) / 100;
		break;

	case 3: //Tri Fusion

		QueryPerformanceFrequency(&freq); // Obtient frequence
		QueryPerformanceCounter(&depart);

		triFusion(tab, taille);

		QueryPerformanceCounter(&fin);
		duree = ((fin.QuadPart - depart.QuadPart) / (float)freq.QuadPart) * 1000000000L;
		duree = ceil(duree * 100) / 100;
		break;

	case 4: //Tri Segmentation

		QueryPerformanceFrequency(&freq); // Obtient frequence
		QueryPerformanceCounter(&depart);

		triSegmentation(tab, taille);

		QueryPerformanceCounter(&fin);
		duree = ((fin.QuadPart - depart.QuadPart) / (float)freq.QuadPart) * 1000000000L;
		duree = ceil(duree * 100) / 100;
		break;

	case 5: //Tri Sort
		
		QueryPerformanceFrequency(&freq); // Obtient frequence
		QueryPerformanceCounter(&depart);

		sort(tab, tab + taille);

		QueryPerformanceCounter(&fin);
		duree = ((fin.QuadPart - depart.QuadPart) / (float)freq.QuadPart) * 1000000000L;
		duree = ceil(duree * 100) / 100;
		break;

	default:
		duree = 0;
	}

	return duree;
}

/*
* fait toutes les comparaisons pour une taille donnée (on donne en paramètre un tableau que l'on remplira)
*/
void compare(int tab[], int taille, double resultats[3][6])
{
	//tableau trie croissant
	for (int i = 0; i <= 5; i++) {
		resultats[0][i] = faireTri(i, tab, taille, 0);
	}
	
	//tableau trie decroissant
	for (int i = 0; i <= 5; i++) {
		resultats[1][i] = faireTri(i, tab, taille, 1);
	}
		
	//tableau aleatoire
	for (int i = 0; i <= 5; i++) {
		resultats[2][i] = faireTri(i, tab, taille, 2);
	}
}


/*
* Imprime les resultats pour une comaraison faite pour une taille donnee
*/
void imprimerResultats(double resultats[3][6], int taille)
{
	cout << "\n\n*********** Resultats ******************" << endl;
	cout << "Taille " << taille << "        - Resultats en nanosecondes" << endl;

	cout << "Tri sur tableau trie : " << endl;
	cout << "Bulles			Selection		Insertion	Fusion		Segmentation		Sort " << endl;
	for (int i = 0; i < 6; i++){
		cout << resultats[0][i] << "		" ;
	}

	cout << "\n\nTri sur tableau trie decroissant : " << endl;
	cout << "Bulles			Selection		Insertion		Fusion		Segmentation		Sort " << endl;
	for (int i = 0; i < 6; i++) {
		cout << resultats[1][i] << "		";
	}

	cout << "\n\nTri sur tableau aleatoire : " << endl;
	cout << "Bulles			Selection		Insertion		Fusion		Segmentation		Sort " << endl;
	for (int i = 0; i < 6; i++) {
		cout << resultats[2][i] << "		";
	}

	cout << "\n****************************************" << endl;
}