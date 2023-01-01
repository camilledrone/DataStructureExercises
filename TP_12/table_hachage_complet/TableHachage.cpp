#include "TableHachage.h"

TableHachage::TableHachage(int m)
{
	this->m = m;					// La taille du tableau
	T = new list<Couple>[m];		// Le tableau de Couple (taille m)
}

TableHachage::~TableHachage()
{
	delete[] T;						// On efface le tableau lors de la destruction de la table de hachage 
									// pour éviter une fuite de mémoire  
									// (Rappel : Si on utilise un pointeur  (new) alors il faut un delete)
}

// Ajout trié dans la liste
void TableHachage::ajouter(int cle, int valeur)
{
	// Trouver la bonne position (ou alvéole) dans le tableau
	int position = hachage(cle);

	// Rechercher dans la liste chainée si CLE existe
	list<Couple>::iterator itCouple;
	for (itCouple = T[position].begin(); itCouple != T[position].end(); itCouple++)
	{
		if ((*itCouple).getCle() == cle) {	//   Si la CLE verifiée est == CLE
			return;							
		}
		if ((*itCouple).getCle() > cle) {	//   Si la CLÉ vérifiée est > CLE
			Couple* c = new Couple(cle, valeur);
			T[position].insert(itCouple, *c);	//     Insérer un nouveau Couple à la position courante (celle de l'itérateur)
			return;
		}
	}
	Couple* c = new Couple(cle, valeur);
	T[position].push_back(*c); // Insérer le nouveau couple à la fin de la liste
}

bool TableHachage::supprimer(int cle)
{
	int position = hachage(cle);

	// Rechercher dans la liste chainée si CLE existe
	list<Couple>::iterator itCouple;
	for (itCouple = T[position].begin(); itCouple != T[position].end(); itCouple++)
	{
		if ((*itCouple).getCle() == cle)  // si c'est le cas, supprime et return true
		{ 
			cout << "Couple (" << cle << " , " << (*itCouple).getValeur() << ") supprime." << endl;
			T[position].erase(itCouple);
			return true;
		}
	}
	return false;
}

/*
* Recherche d'une cle dans la table de hachage
* On recherche aussi un couple car il n'y un qu'un couple par cle
*/
int TableHachage::rechercher(int cle)
{
	int position = hachage(cle);
	list<Couple>::iterator itCouple;
	for (itCouple = T[position].begin(); itCouple != T[position].end(); itCouple++)
	{
		if ((*itCouple).getCle() == cle) // si la cle est dans la liste chainee, retourner la valeur
		{
			return (*itCouple).getValeur();
		}
	}
	return -1; // pas trouve
}

int TableHachage::hachage(int cle)
{
	// La fonction de hachage est : CLE MOD M
	return cle % m;
}

ostream &operator<< (ostream& out, const TableHachage& tableHachage)
{
	list<Couple>::iterator itCouple;

	out << "----------------------" << endl;
	out << "T[], \t(CLE, \tVALEUR)" << endl;
	for (int x = 0; x < tableHachage.m; x++)
		for (itCouple=tableHachage.T[x].begin(); itCouple != tableHachage.T[x].end(); itCouple++)
		{
			out << x << "\t" << (*itCouple);
			out << endl;
		}
	out << "----------------------" << endl;

	return out;
}