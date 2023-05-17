#include <iostream>
#include "MST.h"

using namespace std;
MST myMST;
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
        cout << "4.Algorytm Kruskala" << endl;
        cout << "5.Test (pomiary)" << endl;
        cout << "0.Powrot do menu" << endl;
        cout << "Podaj opcje: ";
        cin >> option;
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
            myMST.kruskal();
            break;
        case '5': 
            myMST.test();
            break;
        }
    } while (option != '0');
}
void menu_ShortestPath() {

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
        cin >> wybor;
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

