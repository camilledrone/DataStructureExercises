#include <iostream>
#include <stdlib.h>
#include <list>
#include "Article.h"
using namespace std;

void ajouterArticle(list<Article>& l, Article article);
void afficherFacture(list<Article>& l);

int main()
{
	list<Article> epicerie;

	Article mesArticles[] =
	{
		Article("Banane", 1, 12),
		Article("Patate", 2, 3),
		Article("Pomme  ", 3, 12),
		Article("Poulet", 10, 1),
		Article("Oeuf  ", 5, 2),
		Article("Cadeau", 30, 2),
		Article("Patate", 1, 50),

	};

	for (Article article : mesArticles) {
		ajouterArticle(epicerie, article);
	}

	afficherFacture(epicerie);

	return 0;
}

/*
* Ajoute un article à la liste tout en conservant un ordre précis.
* L’article le plus couteux (prix * quantité) se retrouve en tête de liste et on continue jusqu’au moins couteux (trié en ordre de prix)
*
*/
void ajouterArticle(list<Article>& l, Article article)
{
	int coutArticle = article.getMontant() * article.getQuantite();
	if (l.empty()) {
		l.push_front(article);
		return;
	}

	//si le cout du nouvel article est plus grand que le premier on peut directement push_front
	if ((l.front().getMontant() * l.front().getQuantite()) <= coutArticle)
	{
		l.push_front(article);
		return;
	}

	//sinon on doit parcourir la liste
	using Iter = std::list<Article>::const_iterator;
	for (Iter it = l.begin(); it != (l.end()); it++) {
		if (((*it).getMontant() * (*it).getQuantite()) <= coutArticle)
		{
			l.insert(it--, article);
			return;
		}
	}
	// si on sort de la boucle c'est que le cout de l'article est plus petit que tous les autres
	l.push_back(article);
}


/*
* Affiche le contenu de la liste ainsi que le total de la facture.
* Utilisation d'un itérateur constant.
*/
void afficherFacture(list<Article>& l)
{
	cout << "  NOM" << "\t\t" << "MONTANT" << "\t" << "QUANTITE" << " TOTAL" << endl;

	int total = 0;
	using Iter = std::list<Article>::const_iterator; //utilisation d'un iterateur constant pour parcourir la liste 
	for (Iter it = l.begin(); it != l.end(); it++) {
		cout << *it << endl; //on utilise la surcharge faite dans la classe Article
		total += (*it).getMontant() * (*it).getQuantite();
	}
	cout << "  TOTAL" << "	----------------------- " << total << endl;
}