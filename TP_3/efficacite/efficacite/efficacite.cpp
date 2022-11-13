#include <stdio.h>
#include <windows.h>
#include <iostream>
using namespace std;

void f1(int n) {
	int somme = 0;							//c0
	for (int i = 0; i < n; i++)				//n
		somme++;							//c1
};

void f2(int n) {
	int somme = 0;							//c0
	for (int i = 0; i < n; i++)				//n
		for (int j = 0; j < n; j++)			//n
			somme++;						//c1
}

void f3(int n) {
	int somme = 0;							//c0
	for (int i = 0; i < n; i++)				//n
		for (int j = 0; j < n * n; j++)		//n²
			somme++;						//c1
}

void f4(int n) {
	int somme = 0;							//c0
	for (int i = 0; i < n; i++)				//n
		for (int j = 0; j < i; j++)			//n
			somme++;						//c1
}

void f5(int n) {
	int somme = 0;							//c0
	for (int i = 0; i < n; i++)				//n
		for (int j = 0; j < i * i; j++)		//n²
			for (int k = 0; k < j; k++)		//n² car j = O(n²)
				somme++;					//c1
}

void f6(int n) {
	int somme = 0;							//c0
	for (int i = 1; i < n; i++)				//n
		for (int j = 1; j < i * i; j++)		//n²
			if (j % i == 0)					//c1	
				for (int k = 0; k < j; k++)	//n, nbJ = nbDiviseursDei <= racine(i)/2 < racine(O(n²)/2 = O(n)
					somme++;				//c2
}

void efficacite() {
	int optionFonction;
	int optionValue;
	cout << "Choisissez la fonction que vous voulez tester (entre 1 et 6) : ";
	cin >> optionFonction;
	cout << "Choisissez la valeur de n pour laquelle vous voulez tester la fonction (0) 10 ou (1) 100 ou (2) ou 1000 ou (3) 10000 : ";
	cin >> optionValue;
	switch (optionFonction)
	{
	case 1:
		f1(optionValue);
		break;
	case 2:
		f2(optionValue);
		break;
	case 3:
		f3(optionValue);
		break;
	case 4:
		f4(optionValue);
		break;
	case 5:
		f5(optionValue);
		break;
	case 6:
		f6(optionValue);
		break;
	default:
		break;
	}
}

int main()
{
	LARGE_INTEGER freq, depart, fin;
	double duree = 0;
	QueryPerformanceFrequency(&freq); // Obtient frequence
	QueryPerformanceCounter(&depart);

	/*
		Mettre votre code ici
	*/
	f6(1000);

	QueryPerformanceCounter(&fin);

	duree = ((fin.QuadPart - depart.QuadPart) / (double)freq.QuadPart) * 1000L;
	printf("Duree: %.4lf millisecondes\n", duree);

	system("pause");
	return 0;
}

