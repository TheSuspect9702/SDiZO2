#include <iostream>
#include <conio.h>
#include "Dijkstra.h"
#include "MST.h"

using namespace std;
MST myMST;
Dijkstra myDijkstra;
void menu_MST() {
    char option;
    string fileName;
    int liczbawierzcholkow;
    int gestosc;
    do {
        cout << endl;
        cout << "=====MST=====" << endl;
        cout << "1.Wczytaj z pliku" << endl;
        cout << "2.Utworz losowo" << endl;
        cout << "3.Wyswietl" << endl;
        cout << "4.Algorytm Prima dla macierzy" << endl;
        cout << "5.Algorytm Prima dla listy" << endl;
        cout << "6.Test (pomiary)" << endl;
        cout << "0.Powrot do menu" << endl;
        cout << "Podaj opcje: ";
        option = _getche();
        cout << endl;
        switch (option) {
        case '1':
            cout << "Podaj nazwe pliku: ";
            cin >> fileName;
            cout << endl;
            myMST.loadFromFile(fileName);
            myMST.display();
            break;
        case '2':
            cout << "Podaj liczbe wierzcholkow: ";
            cin >> liczbawierzcholkow;
            cout << endl << "Podaj gestosc grafu: ";
            cin >> gestosc;
            myMST.generate(liczbawierzcholkow, gestosc);
            myMST.display();
            break;
        case '3':
            myMST.display();
            break;
        case '4':
            myMST.primMacierz();
            cout << "Minimalne drzewo spinajace: " << endl << " ";
            for (int i = 0; i < myMST.liczbaWierzcholkow; i++)
                cout << " " << i;
            for (int i = 0; i < myMST.liczbaWierzcholkow; i++) {
                cout << endl << i << " ";
                for (int j = 0; j < myMST.liczbaWierzcholkow; j++) {
                    cout << myMST.treeMatrix[i][j] << " ";
                }
            }
            cout << endl << "Waga minimalnego drzewa spinajacego: " << myMST.waga;
            break;
        case '5':
            myMST.primLista();
            cout << endl << "LISTA SASIADOW";
            for (int i = 0; i < myMST.treeList.size(); i++) {
                cout << endl << i;
                for (int j = 0; j < myMST.treeList[i].size(); j++) {
                    cout << " => " << myMST.treeList[i][j].v1 << ":" << myMST.treeList[i][j].waga;
                }
            }
            cout << endl << "Waga minimalnego drzewa spinajacego: " << myMST.waga;
            break;
        case '6': 
            myMST.test();
            break;
        }
    } while (option != '0');
}

void menu_ShortestPath() {
    char option;
    string fileName;
    int liczbawierzcholkow;
    int gestosc;
    do {
        cout << endl;
        cout << "=====DIJKSTRA=====" << endl;
        cout << "1.Wczytaj z pliku" << endl;
        cout << "2.Utworz losowo" << endl;
        cout << "3.Wyswietl" << endl;
        cout << "4.Algorytm Prima dla macierzy" << endl;
        cout << "5.Algorytm Prima dla listy" << endl;
        cout << "6.Test (pomiary)" << endl;
        cout << "0.Powrot do menu" << endl;
        cout << "Podaj opcje: ";
        option = _getche();
        cout << endl;
        switch (option) {
        case '1':
            cout << "Podaj nazwe pliku: ";
            cin >> fileName;
            cout << endl;
            myDijkstra.loadFromFile(fileName);
            myDijkstra.display();
            break;
        case '2':
            cout << "Podaj liczbe wierzcholkow: ";
            cin >> liczbawierzcholkow;
            cout << endl << "Podaj gestosc grafu: ";
            cin >> gestosc;
            myDijkstra.generate(liczbawierzcholkow, gestosc);
            myDijkstra.display();
            break;
        case '3':
            myDijkstra.display();
            break;
        case '4':
            break;
        case '5':
            
            break;
        case '6':
            myDijkstra.test();
            break;
        }
    } while (option != '0');
}

int main()
{
    char wybor;
    do {
        cout << "=====MENU=====\n";
        cout << "Wybierz operacje do przetestowania\n";
        cout << "a) Wyznaczenie grafu spojnego (MST)\n";
        cout << "b) Wyznaczenie najkrotszej sciezki\n";
        cout << "c) Zakoncz program\n";
        cout << "Podaj opcje: ";
        wybor = _getche();
        switch (wybor) {
        case 'a':
            menu_MST();
            break;
        case 'b':
            menu_ShortestPath();
            break;
        }
    } while (wybor != 'c');
}

 