#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <list>
#include <string>
using namespace std;

int menu();
void afficherRue(list<int>& l);
void ajouterMaison(list<int>& l);
void supprimerMaison(list<int>& l);
void rechercherMaison(list<int>& l);

int main()
{
	int choix = -1;
	srand(time(NULL));

	// On cree une rue comme une liste d'entiers et on ajoute 5 premieres valeurs
	list<int> rue;
	rue.push_back(401);
	rue.push_back(402);
	rue.push_back(403);
	rue.push_back(405);
	rue.push_back(406);

	while (choix != 4)
	{
		choix = menu();
		switch (choix)
		{
		case 0: afficherRue(rue);
			break;
		case 1: ajouterMaison(rue);
			break;
		case 2: supprimerMaison(rue);
			break;
		case 3: rechercherMaison(rue);
			break;
		}
	}
	cout << "Aurevoir Camille." << endl;
	// fuite de memoire ici mais ne pas considerer pour ce travail
	return 0;
}

int menu()
{
	int choix = -1;

	cout << "\n********************" << endl;
	cout << " 0 - Afficher la rue" << endl;
	cout << " 1 - Ajouter une maison" << endl;
	cout << " 2 - Supprimer une maison" << endl;
	cout << " 3 - Rechercher une maison" << endl;
	cout << " 4 - Quitter la rue" << endl;
	cout << "\n--------------------" << endl;
	cout << " Votre choix? ";

	cin >> choix;
	cout << endl;

	return choix;
}


/*
* Affiche le nombre de maisons de la rue et toutes les maisons (definies par un entier).
*/
void afficherRue(list<int>& l)
{
	cout << "\nVoici la rue (" << l.size() << " maisons) : " << endl;

	using Iter = std::list<int>::const_iterator; //utilisation d'un iterateur constant pour parcourir la liste 
	for (Iter it = l.begin(); it != l.end(); it++) {
		cout << to_string(*it) << "   ";
	}
}


/*
* Fonction appelee par les autres methodes
* Demande un numero civique de maison a l'utilisateur
* Le numero d'une maison doit etre compris entre 400 et 600.
*/
int demandeNumeroCiviqueMaison() {

	int numeroCiviqueMaison;
	cout << "\nQuel est le # civique de la maison (400-600) : ";
	cin >> numeroCiviqueMaison;
	while (numeroCiviqueMaison < 400 || numeroCiviqueMaison >600) {
		cout << "\nVeuillez entrer un entier entre 400 et 600 pour le numero civique : ";
		cin >> numeroCiviqueMaison;
	}
	return numeroCiviqueMaison;
}



/*
* Ajoute une maison (entier) dans la rue (list<int>).
* Le numero d'une maison doit etre compris entre 400 et 600.
* Impossible d'ajouter deux maisons au meme numero/adresse.
*/
void ajouterMaison(list<int>& l) {

	if (l.size() > 200) {
		cout << "\nLa rue est pleine, tous les numeros sont pris, vous ne pouvez plus ajouter de maison. ";
		return;
	}

	int adresseNouvelleMaison = demandeNumeroCiviqueMaison();

	if (l.front() > adresseNouvelleMaison)
	{ //si le numero souhaite est plus petit que tous ceux des maisons de la rue on peut simplement lajouter ua debut
		l.push_front(adresseNouvelleMaison);
		cout << "\n Maison " << adresseNouvelleMaison << " ajoutee !" << endl;
		return;
	}

	//sinon on doit parcourir la liste
	using Iter = std::list<int>::const_iterator;
	for (Iter it = l.begin(); it != (l.end()); it++) {
		if (*it == adresseNouvelleMaison)
		{ //si on tombe sur une maison de la liste avec le meme numero que celui demande
			cout << "\n Maison " << adresseNouvelleMaison << " existe deja !";
			return;
		}

		if (*it > adresseNouvelleMaison)
		{ //si le numero de la maison du pointeur courant est plus grande que celui voulu, on peut inserer la nouvelle maison avant
			l.insert(it--, adresseNouvelleMaison);
			cout << "\n Maison " << adresseNouvelleMaison << " ajoutee !" << endl;
			return;
		}
	}
	// si on sort du for c'est que la rue n'est pas pleine et que le numero demande n'est pas dans la liste et plus grand que tous ceux presents
	l.push_back(adresseNouvelleMaison);
	cout << "\n Maison " << adresseNouvelleMaison << " ajoutee !" << endl;
}


/*
* Supprime une maison (entier) dans la rue (list<int>).
* Le numero d'une maison doit etre compris entre 400 et 600.
* Impossible de supprimer une maison qui n'est pas dans la rue.
*/
void supprimerMaison(list<int>& l) {

	int adresseMaisonASupprimer = demandeNumeroCiviqueMaison();
	using Iter = std::list<int>::const_iterator;
	for (Iter it = l.begin(); it != (l.end()); it++) {
		if (*it == adresseMaisonASupprimer)
		{ //si on tombe sur une maison de la liste avec le meme numero que celui demande
			l.erase(it);
			cout << "\n Maison " << adresseMaisonASupprimer << " supprimee.";
			return;
		}
	}
	//si on sort de la boucle c'est que la maison n'est pas dans la rue
	cout << "\n La maison n'existe pas .";
}


/*
* Recherche une maison (entier) dans la rue (list<int>).
* Le numero d'une maison doit etre compris entre 400 et 600.
*/
void rechercherMaison(list<int>& l)
{
	int adresseMaisonRecherchee = demandeNumeroCiviqueMaison();
	using Iter = std::list<int>::const_iterator;
	for (Iter it = l.begin(); it != (l.end()); it++) {
		if (*it == adresseMaisonRecherchee)
		{ //si on tombe sur une maison de la liste avec le meme numero que celui demande
			cout << "\n La maison " << adresseMaisonRecherchee << "  existe dans la rue.";
			return;
		}
	}
	//si on sort de la boucle c'est que la maison n'est pas dans la rue
	cout << "\n La maison n'existe pas .";
}

