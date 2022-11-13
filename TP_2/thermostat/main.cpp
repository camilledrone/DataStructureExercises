// thermostat.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include <iostream>
#include "thermostat.h"

using namespace std;


int main()
{
	Thermostat* t1 = new Thermostat;
	cout << "Bonjour, vous avez allume le Thermostat Camille ! \n";
    while ((*t1).getState() == 1) {
        
		cout << "\n Options : \n" << "  0 - Arreter le termostat \n" << "  1 - Definir le mode \n" << "  2 - Ajuster la temperature \n" << "  3 - Afficher le thermostat \n" << endl;
		int option;
		cin >> option;
		switch (option) {
		case 0:
			// Stop the thermostat
			(*t1).setState(0);
			break;
		case 1:
			// set the thermostat's mode
			(*t1).changeMode();
			break;
		case 2:
			// Set the temperature depending on the mode
			(*t1).changeTemperature();
			break;
		case 3:
			// display the thermostat
			cout << (*t1) << endl;
			break;
		}
    }
    cout << "\nLe Thermostat Camille va s'eteindre.";
    return 0;
};