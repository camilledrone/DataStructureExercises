#include "thermostat.h"
#include <ostream>
#include <iostream>
#include <string>
using namespace std;

Thermostat::Thermostat(int _state, int _mode, int _numberZones, int _temperature) {
	state = _state;
	mode = _mode;
	numberZones = _numberZones;
	temperature = _temperature;
	temperaturesZones[0] = temperaturesZones[1] = temperaturesZones[2] = 10;
};

Thermostat::Thermostat(int _state, int _mode, int _numberZones, int _temperature, int t[]) {
	state = _state;
	mode = _mode;
	numberZones = _numberZones;
	temperature = _temperature;
	temperaturesZones[0] = t[0];
	temperaturesZones[2] = t[2];
	temperaturesZones[1] = t[1];
};


//surcharge of the operator for the Thermostat class
ostream & operator<<(ostream& os, const Thermostat& t) {
	string thermostat;
	thermostat += "\n-----------------------------------------------\n";
	thermostat += "	THERMOSTAT CAMILLE";
	thermostat += "\n	Mode : ";
	thermostat += t.getMode();
	if (t.mode) {
		// manual mode
		thermostat += "\n	Temperature : ";
		thermostat += to_string(t.temperature);
	}
	else {
		//automatic mode
		for (int i = 0; i < t.numberZones; i++) {
			thermostat += "\n	Temperature Zone (";
			thermostat += to_string(i);
			thermostat += ") : ";
			thermostat += to_string(t.temperaturesZones[i]);
		}
	}
	thermostat += "\n-----------------------------------------------\n";
	os << thermostat;
	return os;
};


void Thermostat::changeMode() {
	//function to change the thermostat's mode to automatic or manual
	int userChoice;
	cout << "Vous voulez changer le mode du thermostat. Le mode actuel est : " << getMode() << "\nChoisissez entre Automatique (0) ou Manuel (1) :  ";
	cin >> userChoice;
	while (userChoice < 0 || userChoice>1) {
		// if the option given by the user is not 1 or 0, the mode is unvalid and the user need to give his choice again
		cout << "Le mode choisi est invalide, choisissez entre Automatique (0) ou Manuel (1) :  ";
		cin >> userChoice;
	}
	setMode(userChoice);
	cout << "Le thermostat est maintenant en mode " << getMode() << "\n";
};


void Thermostat::changeTemperature() {
	// the user can change the temperature or the zones' temperature wether the thermostat is on manual mode or automatic
	int userChoice;
	cout << "\nMode actuel : " << getMode() << "\n";

	if (mode) {
		//manual mode
		cout << "Definir la nouvelle temperature (10-30) : ";
		cin >> userChoice;
		while (userChoice < 10 || userChoice>30) {
			cout << "La temperature choisie est invalide, choisissez une temperature entre 10 et 30 :  ";
			cin >> userChoice;
		}
		setTemperature(userChoice);
	}

	else {
		//automatic mode
		int zoneToModifiy;
		cout << "Choisissez la zone dont vous voulez definir la temperature (0) ou (1) ou (2) : ";
		cin >> zoneToModifiy;
		while (zoneToModifiy < 0 || zoneToModifiy>2) {
			cout << "La zone choisie est invalide, choisissez une zone (0) ou (1) ou (2) :  ";
			cin >> zoneToModifiy;
		}
		cout << "\nDefinir la nouvelle temperature (10-30) : ";
		cin >> userChoice;
		while (userChoice < 10 || userChoice>30) {
			cout << "La temperature choisie est invalide, choisissez une temperature entre 10 et 30 :  ";
			cin >> userChoice;
		}
		setTemperatureZone(zoneToModifiy, userChoice);
	}	
};