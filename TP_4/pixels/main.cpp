#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "Pixel.h"
#include <string>
using namespace std;

void genererPixels(vector<Pixel>& v);
int menu();
void afficherPixels(vector<Pixel>& v);
void afficherOccurences(vector<Pixel>& v);
void rechercherPixel(vector<Pixel>& v);
void modifierTeinte(vector<Pixel>& v);
void insererPixel(vector<Pixel>& v);

int main()
{
	vector<Pixel> v;
	int choix = -1;
	srand(time(NULL));

	genererPixels(v);
	while (choix != 0)
	{
		choix = menu();
		switch (choix)
		{
		case 1: afficherPixels(v);
			break;
		case 2: afficherOccurences(v);
			break;
		case 3: rechercherPixel(v);
			break;
		case 4: modifierTeinte(v);
			break;
		case 5: insererPixel(v);
			break;
		}
	}
	// fuite de memoire ici mais ne pas considerer pour ce travail
	return 0;
}

int menu()
{
	int choix = -1;

	cout << "\n*** MENU ***" << endl;
	cout << " 0 - Quitter" << endl;
	cout << " 1 - Afficher les pixels" << endl;
	cout << " 2 - Afficher les occurences" << endl;
	cout << " 3 - Rechercher un pixel" << endl;
	cout << " 4 - Modifier une teinte" << endl;
	cout << " 5 - Inserer un nouveau pixel" << endl;
	cout << " Votre choix? ";

	cin >> choix;
	cout << endl;

	return choix;
}

///////  SECTION A COMPLETER  /////////

/*
	Demande le nombre de pixels
	Generer (au hasard) et ajoute n pixels dans le vecteur
	Consignes
	- Utiliser la methode "push_back" pour l'insertion
*/
void genererPixels(vector<Pixel>& v)
{
	cout << "*** GENERATIONS DES PIXELS ***" << endl;

	cout << "Nombre de pixels ? ";
	int nombresPixels = -1;
	while (nombresPixels < 0) {
		cin >> nombresPixels;
		if (nombresPixels < 0) {
			cout << "\n Veuillez choisir un nombre de pixels superieur a 0 : ";
		}
	}

	int rouge, vert, bleu;
	for (int i = 0; i < nombresPixels; i++)
	{ //pour chaque pixel a creer on genere aleatoirement leurs valeurs de rouge, vert et bleu entre 0 et 255
		rouge = rand() % 256;
		vert = rand() % 256;
		bleu = rand() % 256;
		v.push_back(Pixel(rouge, vert, bleu));
	}

}


/*
	Affiche tous les pixels du vecteur
	Consignes
	- Utiliser un iterateur constant
	- Ne pas utiliser les operateurs []
*/
void afficherPixels(vector<Pixel>& v)
{
	cout << "\n*** AFFICHER LES PIXELS ***" << endl;

	using Iter = std::vector<Pixel>::const_iterator; //utilisation d'un iterateur constant pour parcourir le vecteur 
	for (Iter it = v.begin(); it != v.end(); it++) {
		cout << *it << endl;
	}
}

/*
	Compte et affiche le nombre de couleurs PURES
		(255, 0, 0), (0, 255, 0) et (0, 0, 255)
	Consignes
	- Utiliser un iterateur constant
	- Ne pas utiliser les operateurs []
*/
void afficherOccurences(vector<Pixel>& v)
{
	cout << "\n*** AFFICHER LES OCCURENCES ***" << endl;

	int nombreRouge = 0, nombreVert = 0, nombreBleu = 0;
	using Iter = std::vector<Pixel>::const_iterator;
	for (Iter it = v.begin(); it != v.end(); it++) {
		if (*it == Pixel(255, 0, 0)) {
			nombreRouge++;
		}
		else if (*it == Pixel(0, 255, 0)) {
			nombreVert++;
		}
		else if (*it == Pixel(0, 0, 255)) {
			nombreBleu++;
		}
	}

	cout << "	Nombre de rouge : " << nombreRouge << endl;
	cout << "	Nombre de vert : " << nombreVert << endl;
	cout << "	Nombre de bleu : " << nombreBleu << endl;
}

/*
	Recherche une couleur en particulier
	On affiche la position de chaque pixel trouve correspondant a la recherche
	Consignes
	- Ne pas utiliser d'iterateur
	- Utiliser les operateurs []
*/
void rechercherPixel(vector<Pixel>& v)
{
	cout << "\n*** RECHERCHE UN PIXEL ***" << endl;

	int pixelRechercheRouge = 0, pixelRechercheVert = 0, pixelRechercheBleu = 0; //teintes du pixel recherche
	cout << "Rouge (0-255) ? ";
	cin >> pixelRechercheRouge;
	cout << "\nVert (0-255) ? ";
	cin >> pixelRechercheVert;
	cout << "\nBleu (0-255) ? ";
	cin >> pixelRechercheBleu;

	string positions;
	using Iter = std::vector<Pixel>::const_iterator;
	int index = 0;
	for (Iter it = v.begin(); it != v.end(); it++, index++)
	{
		if (*it == Pixel(pixelRechercheRouge, pixelRechercheVert, pixelRechercheBleu)) // on utlise la surchage de l'operateur == de la classe Pixel
		{
			int position = &(*it) - &(*v.begin()); //position du pixel dans le vecteur en utilisant l'iterateur et les adresses
			positions.append(to_string(position));
			positions.append(",  ");
		}
	}

	cout << "\nPosition : " << positions << endl;
}

/*
	Choisir une couleur (r/v/b)
	Choisir la quantite de "couleur" a ajouter
	Pour chaque pixel, ajouter la quantite de couleur
	Consignes
	- Utiliser un iterateur (pas constant... evidemment)
	- Ne pas utiliser les operateurs []
	- utiliser les methodes "ajusterXXX" de l'objet Pixel
*/
void modifierTeinte(vector<Pixel>& v)
{
	cout << "\n*** MODIFIER LA TEINTE ***" << endl;

	string couleur;
	cout << "Quelle couleur (r/v/b) ? ";
	cin >> couleur;

	int modificationCouleur;
	cout << "Modification de couleur ? ";
	cin >> modificationCouleur;

	using Iter = vector<Pixel>::iterator; //utilisation d'un iterateur non constant pour parcourir le vecteur 

	if (couleur == "r") {
		for (Iter it = v.begin(); it != v.end(); it++) {
			(*it).ajusterRouge(modificationCouleur);
		}
	}

	if (couleur == "v") {
		for (Iter it = v.begin(); it != v.end(); it++) {
			(*it).ajusterVert(modificationCouleur);
		}
	}

	if (couleur == "b") {
		for (Iter it = v.begin(); it != v.end(); it++) {
			(*it).ajusterBleu(modificationCouleur);
		}
	}
}

/*
	creer un pixel
	Choisir une position
	Si la position est superieur a la taille du vecteur
		Ajouter a la fin du vecteur
	Autrement
		Deplacer un iterateur a la bonne position
		Inserer le pixel (methode insert de vector)
*/
void insererPixel(vector<Pixel>& v)
{
	cout << "\n*** INSERER UN PIXEL ***" << endl;

	int rouge = 0, vert = 0, bleu = 0; //teintes du nouveau pixel
	cout << "\nRouge (0-255) ? ";
	cin >> rouge;
	cout << "\nVert (0-255) ? ";
	cin >> vert;
	cout << "\nBleu (0-255) ? ";
	cin >> bleu;

	int position; //position du nouveau pixel
	cout << "\nPosition (0-" << v.size() - 1 << ") ? ";
	cin >> position;

	if (position >= v.size()) {
		v.push_back(Pixel(rouge, vert, bleu));
	}
	else {
		vector<Pixel>::iterator it;
		it = v.begin() + position; // on deplace l'iterateur a la position a laquelle on veut inserer le pixel
		v.insert(it, Pixel(rouge, vert, bleu)); //insertion a la position de l'iterateur de l'element donne en arguement, les elements apres sont bien deplaces
	}

}