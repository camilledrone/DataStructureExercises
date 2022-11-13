#include "Thermostat.h"
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

// surcharge of the operator << for the Thermostat class
ostream& operator<<(ostream& os, const Thermostat& t) {
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