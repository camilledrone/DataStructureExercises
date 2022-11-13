#include <iostream>
using namespace std;

template<class T>
void permuter(T& a, T& b)
{
	T c = a;
	a = b;
	b = c;
}

template<class T>
void imprimer(T* a, int n)
{
	cout << a[0];
	for (int x = 1; x < n; x++)
		cout << ", " << a[x];
	cout << endl;
}

template<class T>
void triBulles(T* a, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 1; j < n - i; j++)
		{
			if (a[j - 1] > a[j]) {
				permuter(a[j - 1], a[j]);
				//imprimer(a, n);
			}
		}
}

template<class T>
void triSelection(T* a, int n)
{
	int min = 0;
	int j = 0;
	for (int i = 0; i < n - 1; i++) {
		min = i;
		for (j = i + 1; j < n; j++)
			if (a[min] > a[j])
				min = j;
		permuter(a[min], a[i]);
		//imprimer(a, n);
	}
}

template<class T>
void triInsertion(T* a, int n)
{
	int temp = 0;
	int j = 0;
	for (int i = 1; i < n; i++) {
		temp = a[i];
		for (j = i; j > 0 && a[j - 1] > temp; j--)
			a[j] = a[j - 1];
		a[j] = temp;
		//imprimer(a, n);
	}
}


template<class T>
void fusionner(T* a, int n1, int n2)
{
	T* temp = new T[n1 + n2];
	int i = 0;
	int j1 = 0;
	int j2 = 0;
	while (j1 < n1 && j2 < n2)
		temp[i++] = (a[j1] <= a[n1 + j2] ? a[j1++] : a[n1 + j2++]);
	while (j1 < n1)
		temp[i++] = a[j1++];
	while (j2 < n2)
		temp[i++] = a[n1 + j2++];
	for (int i = 0; i < n1 + n2; i++)
		a[i] = temp[i];

	//cout << "F : ";
	//imprimer(temp, n1 + n2);

	delete[] temp;
}

template<class T>
void triFusion(T* a, int n)
{
	//imprimer(a, n);
	if (n > 1)
	{
		int n1 = n / 2;
		int n2 = n - n1;
		triFusion(a, n1);
		triFusion(a + n1, n2);
		fusionner(a, n1, n2);
	}

}

template<class T>
void triSegmentation(T* a, int lo, int hi)
{
	if (lo >= hi)
		return;
	T pivot = a[hi];
	int i = lo - 1;
	int j = hi;
	while (i < j)
	{
		while (a[++i] < pivot);
		while (j >= 0 && a[--j] > pivot);
		if (i < j)
			permuter(a[i], a[j]);
	}
	permuter(a[i], a[hi]);			// Chgangement de pivot!!!!!!!!!!
	triSegmentation(a, lo, i - 1);
	triSegmentation(a, i + 1, hi);
}

template<class T>
void triSegmentation(T* a, int n)
{
	triSegmentation(a, 0, n - 1);
}