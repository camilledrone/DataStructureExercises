#include "Prisme.h"

Prisme::Prisme(string noP, int larg, int lon, int prof)
{
	noPrisme = noP;
	largeur = larg;
	longueur = lon;
	profondeur = prof;
}

Prisme::~Prisme(){}

int Prisme::getVolume() const
{
	return largeur * longueur * profondeur;
}

bool Prisme::operator<(const Prisme& prisme) const
{
	return this->getVolume() < prisme.getVolume();
}

bool Prisme::operator<=(const Prisme& prisme) const
{
	return this->getVolume() <= prisme.getVolume();
}

bool Prisme::operator==(const Prisme& prisme) const
{
	return this->getVolume() == prisme.getVolume();
}

bool Prisme::operator>=(const Prisme& prisme) const
{
	return this->getVolume() >= prisme.getVolume();
}

bool Prisme::operator>(const Prisme& prisme) const
{
	return this->getVolume() > prisme.getVolume();
}

bool Prisme::operator!=(const Prisme& prisme) const
{
	return this->getVolume() != prisme.getVolume();
}

ostream& operator<< (ostream& out, const Prisme& prisme)
{
	out << "NO VOLUME    : " << prisme.noPrisme << " (" << prisme.getVolume() << ")" << endl;
	out << "  LARGEUR    : " << prisme.largeur << endl;
	out << "  LONGUEUR   : " << prisme.longueur << endl;
	out << "  PROFONDEUR : " << prisme.profondeur << endl;
	return out;
}

Prisme& Prisme::operator=(const Prisme& prisme)
{
	if( this == &prisme)
		return *this;

	largeur = prisme.largeur;
	longueur = prisme.longueur;
	profondeur = prisme.profondeur;
	noPrisme = prisme.noPrisme;

	return *this;
}