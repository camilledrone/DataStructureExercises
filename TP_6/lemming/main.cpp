#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <list>
#include <string>
#include "Lemming.h"
#include <queue>
#include <stack>
using namespace std;

void displayLemmings(list<Lemming>& l);
void displayLemmings(queue<Lemming>& q);
void step1Gathering(list<Lemming>& l, int nbLemmings);
void step2DarkPassageWay(list<Lemming>& lemmingGathering, queue<Lemming>& lemmingDarkPassageWay);
void step3Slop(queue<Lemming>& lemmingDarkPassageWay, queue<Lemming>& lemmingSlop);
void step4Ladder(queue<Lemming>& lemmingSlop, list<Lemming>& lemmingLadder);
void step5Srpint(list<Lemming>& lemmingLadder, queue<Lemming>& lemmingSprint);
void step6Freedom(queue<Lemming>& lemmingSprint, list<Lemming>& lemmingsMissing, queue<Lemming>& lemmingSurviving);

int main()
{
	// STEP 1 
	cout << "\nSTEP #1 : The gathering" << endl;
	list<Lemming> lemmingGathering;
	step1Gathering(lemmingGathering, 20);
	displayLemmings(lemmingGathering);

	// STEP 2
	cout << "\n\nSTEP #2 : The dark passageway" << endl;
	queue<Lemming> lemmingDarkPassageWay;
	step2DarkPassageWay(lemmingGathering, lemmingDarkPassageWay);
	displayLemmings(lemmingDarkPassageWay);

	// STEP 3 
	cout << "\n\nSTEP #3 : The slop" << endl;
	queue<Lemming> lemmingSlop;
	step3Slop(lemmingDarkPassageWay, lemmingSlop);
	displayLemmings(lemmingSlop);

	// STEP 4 
	cout << "\n\nSTEP #4 : The ladder" << endl;
	list<Lemming> lemmingLadder;
	step4Ladder(lemmingSlop, lemmingLadder);
	displayLemmings(lemmingLadder);

	// STEP 5 
	cout << "\n\nSTEP #5 : The sprint" << endl;
	queue<Lemming> lemmingSprint;
	step5Srpint(lemmingLadder, lemmingSprint);
	displayLemmings(lemmingSprint);

	// STEP 6 
	cout << "\n\nSTEP #6 : Freedom !!" << endl;
	list<Lemming> lemmingsMissing;
	queue<Lemming> lemmingSurviving;
	step6Freedom(lemmingSprint, lemmingsMissing, lemmingSurviving);
	displayLemmings(lemmingSurviving);
	displayLemmings(lemmingsMissing);


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


// function to display a queue of Lemmings
void displayLemmings(queue<Lemming>& q)
{
	cout << "File (" << q.size() << " ) : " << q.front() << "  <--  " << q.back() << endl;
}




/*
* 20 lemmings are created one after the other and in order
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
* The lemmings enter the cave but the passage is narrow and very dark. They have to walk through it in single file.
* transfer the contents of the list (step#1) to the queue
*/
void step2DarkPassageWay(list<Lemming>& lemmingGathering, queue<Lemming>& lemmingDarkPassageWay)
{
	for (auto it = lemmingGathering.rbegin(); it != lemmingGathering.rend(); it++) {
		lemmingDarkPassageWay.push(*it);
	}

}


/*
* The lemmings are making progress on a steep and slippery slope. Unfortunately, some of them slip and die!
* transfer the contents of the queue (step #2) to the new queue (step #3). Each lemming has a 5% chance of dying
*/
void step3Slop(queue<Lemming>& lemmingDarkPassageWay, queue<Lemming>& lemmingSlop)
{
	srand(time(NULL));
	int numberLemming = 1; // integer in the situation where a lemming dies to know his number

	// The queue does not support the lookup operation, 
	// to get the lemmings and transfer them to the new queue one must scroll
	while (!lemmingDarkPassageWay.empty())
	{
		int randomInt = rand() % 101;
		if (randomInt <= 95) {
			//the lemming has 5% chance of being transfered in the new queue
			lemmingSlop.push(lemmingDarkPassageWay.front());
		}
		else {
			cout << "The Lemming " << numberLemming << " slips and dies ! " << endl;
		}
		numberLemming++;
		lemmingDarkPassageWay.pop();
	}
}


/*
* The lemmings find themselves facing a steep cliff. They create a long, living ladder which allows them to continue.
* The lemmings forming the ladder join the group using a rope (the lemmings climb from the highest to the lowest).
*
* Creating the ladder: transfer the first 10 lemmings from the queue (step #3) to a stack.
* The lemmings climb the ladder: transferring the rest of the elements in the queue to a list.
* The rope: unravelling the lemmings to the list
*
*/
void step4Ladder(queue<Lemming>& lemmingSlop, list<Lemming>& lemmingLadder)
{

	//step 1 creating the ladder
	stack<Lemming> tempStack;
	int numberLemming = 0;
	while (numberLemming < 10) {
		tempStack.push(lemmingSlop.front());
		lemmingSlop.pop();
		numberLemming++;
	}

	//step 2 climb the ladder
	while (!lemmingSlop.empty()) {
		lemmingLadder.push_front(lemmingSlop.front());
		lemmingSlop.pop();
	}

	//step 3 the rope
	while (!tempStack.empty()) {
		lemmingLadder.push_front(tempStack.top());
		tempStack.pop();
	}

}


/*
* The lemmings hear noises and panic. They run down the corridor and some of them are are simply crushed by a clever but deadly trap!
*
* transfer the contents of the list to the queue. Before transfer them, choose 5 lemmings at random.
* These have a 50% chance of succumbing (and not be added to the queue).
*/
void step5Srpint(list<Lemming>& lemmingLadder, queue<Lemming>& lemmingSprint)
{
	int numberLemmings = lemmingLadder.size();
	vector<int> selectedLemmings;
	srand(time(NULL));

	// choose the 5 lemmings
	while (selectedLemmings.size() < 5) {
		int randomInt = rand() % numberLemmings;
		// if the indice i is not in the vector of the selected lemmings already
		if (std::find(selectedLemmings.begin(), selectedLemmings.end(), randomInt) == selectedLemmings.end()) {
			selectedLemmings.push_back(randomInt);
		}
	}

	int i = 0;
	//transfer from the list to the queue, if the lemming is in the selected Lemmings we have to see if he survives or not
	for (auto it = lemmingLadder.rbegin(); it != lemmingLadder.rend(); it++) {
		// if the indice i is in the vector of the selected lemmings
		if (std::find(selectedLemmings.begin(), selectedLemmings.end(), i) != selectedLemmings.end()) {
			int chanceOfDying = rand() % 2;
			if (chanceOfDying < 1) {
				lemmingSprint.push(*it);
			}
			else {
				cout << "The lemming " << *it << " is victim of the trap !" << endl;
			}
		}
		else {
			lemmingSprint.push(*it);
		}
		i++;
	}
	lemmingLadder.clear();
}


/*
* The lemmings are nearing the end of the cave, the light is at the end of the tunnel.
* They must jump over a bottomless pit by clinging to strange vines hanging from the ceiling...
*
* Each lemming has a 20% chance of falling
* Lemming falls: transfer the lemming from the queue to a list of missing lemmings
* The lemming is free: transfer the lemming from the queue to a queue of surviving lemmings
*
*/
void step6Freedom(queue<Lemming>& lemmingSprint, list<Lemming>& lemmingsMissing, queue<Lemming>& lemmingSurviving)
{
	srand(time(NULL));

	while (!lemmingSprint.empty()) {
		Lemming lemming = lemmingSprint.front();
		int chanceOfFalling = rand() % 101;
		if (chanceOfFalling < 20)
		{
			lemmingsMissing.push_front(lemming);
			cout << "The lemming " << lemming << " lets go of the tether and falls into the bottomless pit !" << endl;
		}
		else
		{
			lemmingSurviving.push(lemming);
		}
		lemmingSprint.pop();
	}
}