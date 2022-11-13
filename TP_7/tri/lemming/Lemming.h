#ifndef LEMMING_H
#define LEMMING_H

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>  
using namespace std;

class Lemming
{
private:
	int id;
	static int count;
	static vector<int>* lemmingsCreated;
	int GenerateId(vector<int>& lemmingsCreated);


public:
	Lemming() { id = GenerateId(*lemmingsCreated); (*lemmingsCreated).push_back(id); }
	int getId() { return id; }
	friend ostream& operator<< (ostream&, const Lemming&);
	friend bool operator< (const Lemming&, const Lemming&);


};

int Lemming::count = 0;
vector<int>* Lemming::lemmingsCreated = new vector<int>();

ostream& operator<< (ostream& out, const Lemming& lemming)
{
	out << lemming.id;
	return out;
}

bool operator< (const Lemming& lemming1, const Lemming& lemming2)
{
	return(lemming1.id < lemming2.id);
}


/*
* generate a random id for the new lemming
* the id must be unique
*/
int Lemming::GenerateId(vector<int>& lemmingsCreated)
{
	int newid;
	bool isValid = false;
	srand(time(NULL));

	while (!isValid) {
		newid = rand() % 51 + 1;
		if (!(find(lemmingsCreated.begin(), lemmingsCreated.end(), newid) != lemmingsCreated.end())) {
			isValid = true;
		}
	}
	return newid;
}


#endif
