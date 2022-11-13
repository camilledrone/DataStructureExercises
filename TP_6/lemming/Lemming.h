#ifndef LEMMING_H
#define LEMMING_H

#include <iostream>
using namespace std;

class Lemming
{
private:
	int id;
	static int count;

public:
	Lemming() { id = ++count; }
	friend ostream& operator<< (ostream&, const Lemming&);
	int getId() { return id; }

};

int Lemming::count = 0;

ostream& operator<< (ostream& out, const Lemming& lemming)
{
	out << lemming.id;
	return out;
}


#endif