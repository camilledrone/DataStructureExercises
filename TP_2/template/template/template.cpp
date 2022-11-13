#include <iostream>
#include <ostream>
#include <string>
#include "Thermostat.h"
using namespace std;

template <class T>
void display(T& obj) {
    cout << obj << endl;
}

int main()
{
    int i = 100;
    float f = 8.109;
    string s = "Bienvenue Camille";
    Thermostat* t1 = new Thermostat;

    cout << "\nAFFICHER INT : ";
    display<int>(i);
    cout << "\nAFFICHER FLOAT : ";
    display<float>(f);
    cout << "\nAFFICHER STRING : ";
    display<string>(s);
    cout << "\nAFFICHER THERMOSTAT : ";
    display<Thermostat>(*t1);

    return 0;
}
