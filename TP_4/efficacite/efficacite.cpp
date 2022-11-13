#include <iostream>
#include <string>
#include <stdio.h>
#include <windows.h>
#include <vector>
#include <stdlib.h>     
#include <time.h> 
using namespace std;

//insertion de N entiers aleatoires dans un tableau
void testTab(int N)
{
    std::cout << "\n\ntestTab : Insertion dans un tableau ";
    double dureeTotale = 0;
    int entier; //entier que l'on generera aletatoirement puis inserera dans le tableau
    int tab[100000];

    for (int i = 0; i < N; i++) {
        srand(time(NULL));
        entier = rand() % N;

        LARGE_INTEGER freq, depart, fin;
        double duree;
        QueryPerformanceFrequency(&freq); // Obtient frequence
        QueryPerformanceCounter(&depart);

        tab[i] = entier;

        QueryPerformanceCounter(&fin);

        duree = ((fin.QuadPart - depart.QuadPart) / (double)freq.QuadPart) * 1000L;
        dureeTotale += duree;
    }

    double moyenne = dureeTotale / N;
    std::cout << "\n N : " << N;
    std::cout << "\n Duree : " << dureeTotale << " ms";
    std::cout << "\n Moyenne : " << moyenne << " ms";

}

//insertion de N entiers aleatoires dans un vecteur sans taille specifique a la creation (push back)
void testV1(int N)
{
    std::cout << "\n\ntestV1 : Insertion dans un vecteur ";
    double dureeTotale = 0;
    int entier;
    vector<int> vect;

    for (int i = 0; i < N; i++) {
        srand(time(NULL));
        entier = rand() % N;

        LARGE_INTEGER freq, depart, fin;
        double duree = 1;
        QueryPerformanceFrequency(&freq); // Obtient frequence
        QueryPerformanceCounter(&depart);

        vect.push_back(entier);

        QueryPerformanceCounter(&fin);

        duree = ((fin.QuadPart - depart.QuadPart) / (double)freq.QuadPart) * 1000L;
        dureeTotale += duree;
    }

    double moyenne = dureeTotale / N;
    std::cout << "\n N : " << N;
    std::printf("\n  Duree: %.4lf millisecondes", dureeTotale);
    std::printf("\n  Moyenne: %.4lf millisecondes", moyenne);
}

//testV1 + moment auquel le vecteur effectue l'operation d'insertion + liste des points de reserve (15)
void testV2(int N)
{
    std::cout << "\n\ntestV2 :";
    int capaciteInitiale = 0;
    int capacity = 0;
    double dureeTotale = 0;
    int entier;
    vector<int> vect;
    string pointsReserve;
    int ptRserve = 0;

    for (int i = 0; i < N; i++) {
        srand(time(NULL));
        entier = rand() % N;

        LARGE_INTEGER freq, depart, fin;
        double duree = 1;
        QueryPerformanceFrequency(&freq); // Obtient frequence
        QueryPerformanceCounter(&depart);

        vect.push_back(entier);

        QueryPerformanceCounter(&fin);
        duree = ((fin.QuadPart - depart.QuadPart) / (double)freq.QuadPart) * 1000L;
        dureeTotale += duree;
        if (ptRserve < 16) {
            if (vect.capacity() > capacity) {
                capacity = vect.capacity();
                ptRserve++;
                pointsReserve.append("\n Capacity : ");
                pointsReserve.append(std::to_string(capacity));
                pointsReserve.append("   duree : ");
                pointsReserve.append(std::to_string(duree));
                pointsReserve.append("  ms ");
            }

        }
    }

    double moyenne = dureeTotale / N;
    std::cout << "\n N : " << N;
    std::cout << "\n Capacite Initiale : " << capaciteInitiale;
    std::printf("\n  Moyenne: %.4lf millisecondes", moyenne);
    std::cout << "\n Points de reserve ? " << pointsReserve;
}


int main()
{
    std::cout << "Hello Camille!\n";

    int N = 10;

    testTab(N);
    testTab(N * 100);
    testTab(N * 10000);

    N = 1000;
    testV1(N);
    testV1(N * 100);
    testV1(N * 10000);

    testV2(N);

    return 0;
}