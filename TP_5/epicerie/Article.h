/*
	****** ATTENTION : Cette classe ne doit pas etre modifiee ******
*/

#ifndef ARTICLE_H
#define ARTICLE_H

#include <iostream>
#include <string>
using namespace std;

class Article
{
public:
	Article(string nom, int montant, int quantite) { _nom = nom; _montant = montant; _quantite = quantite; }

	string getNom() const { return _nom; }
	int getMontant() const { return _montant; }
	int getQuantite() const { return _quantite; }

	friend ostream& operator<< (ostream&, const Article& article);

private:
	string _nom;
	int _montant;
	int _quantite;
};

ostream& operator<< (ostream& out, const Article& article)
{
	out << "- " << article._nom << "\t" << article._montant << "\t" << article._quantite << "\t" << (article._quantite * article._montant);
	return out;
}


#endif 