#pragma once
#include <string>
#include <ostream>
using namespace std;

class Thermostat
	// Thermostat troncated class, with just the fonciton for displaying, to setting or changement available
{
public:
	Thermostat() : Thermostat(1, 0, 3, 10) {};// constructeur par défaut
	Thermostat(int state, int mode, int numberZones, int temperature);  //constructeur thermostat personnalise
	~Thermostat(); //destructeur

	friend ostream& operator<< (ostream& os, const Thermostat& t); //operator's surcharge to display the thermostat
	string getMode() const {
		if (mode) return "Manuel"; return "Automatique";
	}

private:
	int state; // 0 off and 1 on
	int mode; // mode 0 : automatic and mode 1 : manual
	int numberZones;
	int temperature; //temperature in manual mode
	int temperaturesZones[3]; //the three zones' temperature
};

