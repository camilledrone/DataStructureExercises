#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <list>
#include <string>
#include "Lemming.h"
#include <algorithm>
using namespace std;


void displayLemmings(list<Lemming>& l);
void step1Gathering(list<Lemming>& l, int nbLemmings);
void step2Sorting(list<Lemming>& l, int nbLemmings);

int main()
{
	// STEP 1 
	cout << "\nSTEP 1 : The gathering" << endl;
	list<Lemming> lemmingGathering;
	step1Gathering(lemmingGathering, 50);
	displayLemmings(lemmingGathering);


	// STEP 2 
	cout << "\nSTEP 2 : Sort" << endl;
	step2Sorting(lemmingGathering, 50);
	displayLemmings(lemmingGathering);


	return 0;
}


// function to display a list of Lemmings
void displayLemmings(list<Lemming>& l)
{
	cout << "List (" << l.size() << " ) : ";

	for (auto it = l.rbegin(); it != l.rend(); it++) {
		cout << *it << "  <-  ";
	}

	cout << endl;
}

/*
* 50 lemmings are created one after the other with random id between 1 and 50
* and are added to a list
*/
void step1Gathering(list<Lemming>& l, int nbLemmings)
{
	for (int i = 0; i < nbLemmings; i++) {
		Lemming* lemming = new Lemming();
		l.push_front(*lemming);
	}
}


/*
* The lemmings are sorted with the function "sort" included in the STL list
*/
void step2Sorting(list<Lemming>& l, int nbLemmings)
{
	//compare used in the sort fonction is the overload of the operator < for the class Lemming
	l.sort();
}