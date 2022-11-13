#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include "Prisme.h"
#include "arbreBST.cpp"

using namespace std;

void chargerPrismes(BinarySearchTree<Prisme>& prismes);
void supprimerPiresCas(BinarySearchTree<Prisme>& prismes);
Prisme creerRecherche();
void rechercherPrisme(BinarySearchTree<Prisme>& prismes, Prisme prismeRecherche);
void rechercherPrisme(BinarySearchTree<Prisme>& prismes);
void imprimerPrismes(BinarySearchTree<Prisme>& prismes);

int main(int argc, char *argv[])
{
	BinarySearchTree<Prisme> prismes;
	chargerPrismes(prismes);

	cout << "----------------------------------------------------" << endl;
	cout << "ETAPE #1 : Impression de l'arbre dans un fichier" << endl;
	cout << "----------------------------------------------------" << endl;
	imprimerPrismes(prismes);

	cout << endl;
	cout << "----------------------------------------------------" << endl;
	cout << "ETAPE #2 : Recherche d'une valeur" << endl;
	cout << "----------------------------------------------------" << endl;
	rechercherPrisme(prismes);

	cout << endl;
	cout << "----------------------------------------------------" << endl;
	cout << "ETAPE #3 : Suppression des pires cas" << endl;
	cout << "----------------------------------------------------" << endl;
	supprimerPiresCas(prismes);

	cout << endl;
	cout << "----------------------------------------------------" << endl;
	cout << "ETAPE #4 : Recherche du meilleur cas selon des criteres" << endl;
	cout << "----------------------------------------------------" << endl;
	rechercherPrisme(prismes, creerRecherche());

    system("PAUSE");
    return EXIT_SUCCESS;
}

/* 
	Charger tous les prismes a partir du fichier "prismes.dat"
	Inserer dans l'arbre dans l'ordre de lecture
*/
void chargerPrismes(BinarySearchTree<Prisme>& prismes)
{
	ifstream in("prismes.dat");
	string numero;
	int longueur, largeur, profondeur;
	while (in >> numero >> longueur >> largeur >> profondeur) //Tant qu'on n'est pas à la fin, on lit
	{
		Prisme* prisme = new Prisme(numero, longueur, largeur, profondeur);
		prismes.insert(*prisme); 
	}
	in.close();
}

/* 
	A FAIRE :	Completer la surcharge de l'operateur << dans l'arbre afin d'afficher tous les prismes en ordre croissant de volume dans le fichier
				(Refererence : methode parcours dans la theorie)
*/
void imprimerPrismes(BinarySearchTree<Prisme>& prismes)
{
	ofstream out ("prismes.txt");
	out << prismes;
	out.close();
}

/* 
	Supprime les pires cas de l'arbre
*/
void supprimerPiresCas(BinarySearchTree<Prisme>& prismes)
{
	int nombreCasASupprimer = -1;
	cout << "Combien de pires cas doivent etre supprimes ? ";
	cin >> nombreCasASupprimer;

	while (nombreCasASupprimer != 0) {

		//si l'arbre est vide
		if (prismes.isEmpty()) {
			cout << "L'arbre est deja vide, on ne peut pas supprimer " << nombreCasASupprimer << " cas." << endl;
			nombreCasASupprimer = 0;
		}
		else {
			cout << "Suppression du pire cas #" << nombreCasASupprimer << endl;
			cout << prismes.findMin() <<endl;
			prismes.remove(prismes.findMin());
			nombreCasASupprimer--;
		}
		
	}

}

/* 
	Recherche le MEILLEUR prisme qui correspond aux criteres minimums de la recherche
	Si le meilleur prisme ne correspond pas, on passe au meilleur suivant
	Si il correspond, on l'affiche
*/
void rechercherPrisme(BinarySearchTree<Prisme>& prismes, Prisme prismeRecherche)
{
	//on fait une copie de l'arbre pour pouvoir supprimer au fur et a mesure les prismes max qu'on a regarde
	BinarySearchTree<Prisme> copie = prismes;
	bool trouve = false;
	int n = 1;

	//tant qu'on a pas trouve ou que l'arbre copie contient encore au moins un noeud
	while (!trouve && !copie.isEmpty()) {
		Prisme prismeMax = copie.findMax();
		cout << "Verification du prisme #" << n << endl;
		if ((prismeMax.getLargeur() >= prismeRecherche.getLargeur()) && (prismeMax.getLongueur() >= prismeRecherche.getLongueur()) && (prismeMax.getProfondeur() >= prismeRecherche.getProfondeur()))
		{
			cout << "Voici le meilleur prisme trouve : " << endl;
			cout << prismeMax << endl;
			trouve = true;
		}
		else {
			copie.remove(prismeMax);
			n++;
		}
	}
	if (!trouve) {
		cout << "\nLe prisme avec le profil demande n'existe pas." << endl;
	}
	
}

/* 
	Recherche d'un prisme par VOLUME donne par l'utilisateur dans l'interface
*/
void rechercherPrisme(BinarySearchTree<Prisme>& prismes)
{
	// demande du volume recherche
	int volume = -1;
	cout << "Entrer un volume a rechercher (valeur positive exacte) : " ;
	cin >> volume; 

	// validation de la saisie d'un resultat positifs
	while (volume < 0)
	{
		cout << "\nVolume invalide, valeur positive seulement : ";
		cin >> volume;
	}

	// recherche
	Prisme* prismeRecherche = new Prisme("recherche", volume, 1, 1);
	bool estDansArbre = prismes.contains(*prismeRecherche);
	if (estDansArbre)
	{
		cout << "\nCe profil existe bien." << endl;
	}
	else 
	{
		cout << "\nUn prisme avec le profil demande n'existe pas." << endl;
	}	

	delete prismeRecherche;
}

// Celle la est complete!
Prisme creerRecherche()
{
	Prisme p("RECHERCHE", 0, 0, 0);
	int valeur;

	cout << "Entrer vos critères de recherche  (0 = aucun)" << endl;
	cout << "  Entrer la largeur minimum : ";
	cin >> valeur;
	p.setLargeur(valeur);

	cout << "  Entrer la longueur minimum : ";
	cin >> valeur;
	p.setLongueur(valeur);

	cout << "  Entrer la profondeur minimum : ";
	cin >> valeur;
	p.setProfondeur(valeur);

	return p;
}
