#pragma once
using namespace std;
#include <ostream>;
#include <string>;


class Thermostat
{
public:

	Thermostat() : Thermostat(1, 0, 3, 10 ) {};// constructeur par défaut
	Thermostat(int state, int mode, int numberZones, int temperature);  //constructeur thermostat personnalised
	Thermostat(int state, int mode, int numberZones, int temperature, int* t);  //constructeur thermostat personnalised
	~Thermostat(); //destructeur

	friend ostream& operator<< (ostream& os, const Thermostat& t); //operator's surcharge to display the thermostat
	int getState() const { return state; };
	string getMode() const {
		if (mode) return "Manuel"; return "Automatique";
	}
	void displayThermostat();
	void setMode(int numeroMode) { mode = numeroMode; }
	void setState(int _state) { state = _state; }
	void setTemperatureZone(int numeroZone, int temperatureSouhaitee) { temperaturesZones[numeroZone] = temperatureSouhaitee; }
	void setTemperature(int temperatureSouhaitee) { temperature = temperatureSouhaitee; }
	void changeTemperature();
	void changeMode();

private : 
	int state; // 0 off and 1 on
	int mode; // mode 0 : automatic and mode 1 : manual
	int numberZones;
	int temperature; //temperature in manual mode
	int temperaturesZones[3]; //the three zones' temperature
};

