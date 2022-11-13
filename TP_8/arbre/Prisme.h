#ifndef PRISME_H
#define PRISME_H

#include <iostream>
#include <string>
using namespace std;

class Prisme
{
public:
	Prisme(string noPrisme, int larg, int lon, int prof);
	~Prisme();

	// Accesseurs
	string getNoPrisme() const {return noPrisme;}
	int getLargeur() const {return largeur;}
	int getLongueur() const {return longueur;}
	int getProfondeur() const {return profondeur;}
	void setLargeur(int la) {largeur = la;}
	void setLongueur(int lo) {longueur = lo;}
	void setProfondeur(int pr) {profondeur = pr;} 

	// Surcharge des opérateurs
	bool operator<(const Prisme& prisme) const;
	bool operator<=(const Prisme& prisme) const;
	bool operator==(const Prisme& prisme) const;
	bool operator>=(const Prisme& prisme) const;
	bool operator>(const Prisme& prisme) const;
	bool operator!=(const Prisme& prisme) const;

	friend ostream &operator<< (ostream& out, const Prisme& prisme);
	Prisme& operator=(const Prisme& prisme);

private:

	int getVolume() const;

	string noPrisme;
	int largeur;
	int longueur;
	int profondeur;
};

#endif
