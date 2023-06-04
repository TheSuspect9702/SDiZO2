#include "Dijkstra.h"
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <queue>
#include <algorithm>
using namespace std;


void Dijkstra::clearDijkstraMacierz()
{
	tablicaDikstra.clear();
	delete[] macierzDijkstra;
}

void Dijkstra::clearDijkstraList()
{
	tablicaDikstra.clear();
	listaSasiadowDijkstra.clear();
}



void Dijkstra::loadFromFile(string fileName)
{
	clear();
	ifstream read(fileName);
	string dane;
	read >> dane;
	liczbaKrawedzi = stoi(dane);
	read >> dane;
	liczbaWierzcholkow = stoi(dane);
	read >> dane;
	first = stoi(dane);
	macierz = new int* [liczbaWierzcholkow];
	for (int i = 0; i < liczbaWierzcholkow; i++) {
		int* temp = new int[liczbaWierzcholkow];
		vector<sasiedzi> nowySasiad;
		listaSasiadow.push_back(nowySasiad);
		for (int j = 0; j < liczbaWierzcholkow; j++) {
			temp[j] = 0;
		}
		macierz[i] = temp;
	}
	int w1, w2, w;
	for (int i = 0; i < liczbaKrawedzi; i++) {
		sasiedzi nowysasiad;
		read >> dane;
		w1 = stoi(dane);
		read >> dane;
		w2 = stoi(dane);
		read >> dane;
		w = stoi(dane);
		nowysasiad.v1 = w2;
		nowysasiad.waga = w;
		nowysasiad.visited = false;
		macierz[w1][w2] = w;
		listaSasiadow[w1].push_back(nowysasiad);
	}
	read.close();

}

void Dijkstra::display()
{
	cout << "MACIERZ SASIEDZTWA" << endl << " ";
	for (int i = 0; i < liczbaWierzcholkow; i++)
		cout << " " << i;
	for (int i = 0; i < liczbaWierzcholkow; i++) {
		cout << endl << i << " ";
		for (int j = 0; j < liczbaWierzcholkow; j++) {
			cout << macierz[i][j] << " ";
		}

	}
	cout << endl << "LISTA SASIADOW";
	for (int i = 0; i < listaSasiadow.size(); i++) {
		cout << endl << i;
		for (int j = 0; j < listaSasiadow[i].size(); j++) {
			cout << " => " << listaSasiadow[i][j].v1 << ":" << listaSasiadow[i][j].waga;
		}
	}
}

void Dijkstra::generate(int liczbaWierzcholkow1, int gestosc)
{
	srand(time(NULL));
	clear();
	liczbaWierzcholkow = liczbaWierzcholkow1;
	macierz = new int* [liczbaWierzcholkow];
	liczbaKrawedzi = liczbaWierzcholkow * (liczbaWierzcholkow - 1) / 2 * gestosc / 100;
	int pozostaleKrawedzie = liczbaKrawedzi;
	int value;
	//inicjalizacja macierzy i listy sasiadow
	for (int i = 0; i < liczbaWierzcholkow; i++) {
		int* temp = new int[liczbaWierzcholkow];
		vector<sasiedzi> nowySasiad;
		listaSasiadow.push_back(nowySasiad);
		for (int j = 0; j < liczbaWierzcholkow; j++) {
			temp[j] = 0;
		}
		macierz[i] = temp;
	}
	//stworzenie drzewa rozpinajacego
	for (int i = 1; i < liczbaWierzcholkow; i++) {
		sasiedzi nowySasiad;
		value = rand() % liczbaWierzcholkow + 1;
		macierz[i - 1][i] = value;
		nowySasiad.v1 = i;
		nowySasiad.waga = value;
		listaSasiadow[i - 1].push_back(nowySasiad);
		pozostaleKrawedzie--;
	}
	int v1, v2;
	//dodanie pozosta³ych krawedzi
	while (pozostaleKrawedzie > 0) {
		v1 = rand() % liczbaWierzcholkow;
		v2 = rand() % liczbaWierzcholkow;
		if (v1 == v2 || macierz[v1][v2] != 0)
			continue;
		value = rand() % liczbaWierzcholkow + 1;
		sasiedzi nowySasiad;
		macierz[v1][v2] = value;
		nowySasiad.v1 = v2;
		nowySasiad.waga = value;
		listaSasiadow[v1].push_back(nowySasiad);
		pozostaleKrawedzie--;
	}
}

void Dijkstra::dijkstraMacierz()
{
	int current = first;
	clearDijkstraMacierz();
	for (int i = 0; i < liczbaWierzcholkow; i++) {
		sasiedzi nowysasiad;
		nowysasiad.visited = false;
		nowysasiad.v1 = liczbaWierzcholkow;
		nowysasiad.waga = -1;
		tablicaDikstra.push_back(nowysasiad);
	}
	tablicaDikstra[first].waga = 0;
	tablicaDikstra[first].v1 = -1;
	do {
		tablicaDikstra[current].visited = true;
		for (int i = 0; i < liczbaWierzcholkow; i++) {
			if (macierz[current][i] > 0 && i != first && (macierz[current][i] + tablicaDikstra[current].waga < tablicaDikstra[i].waga || tablicaDikstra[i].waga == -1)) {
				tablicaDikstra[i].v1 = current;
				tablicaDikstra[i].waga = macierz[current][i] + tablicaDikstra[current].waga;
			}
		}
		for (int i = 0; i < tablicaDikstra.size(); i++) {
			if (tablicaDikstra[i].waga > 0 && !tablicaDikstra[i].visited && tablicaDikstra[current].visited) {
				current = i;
			}
			else if (tablicaDikstra[i].waga < tablicaDikstra[current].waga && !tablicaDikstra[current].visited && tablicaDikstra[i].waga > 0 && !tablicaDikstra[i].visited) {
				current = i;
			}
		}
		if(tablicaDikstra[current].visited)
			for (int i = 0; i < tablicaDikstra.size(); i++) {
				if (!tablicaDikstra[i].visited && tablicaDikstra[current].visited) {
					current = i;
				}
				else if (!tablicaDikstra[i].visited && tablicaDikstra[i].waga < tablicaDikstra[current].waga) {
					current = i;
				}
			}
	} while (!tablicaDikstra[current].visited);
	macierzDijkstra = new int* [liczbaWierzcholkow];
	for (int i = 0; i < liczbaWierzcholkow; i++) {
		int* temp = new int[liczbaWierzcholkow];
		for (int j = 0; j < liczbaWierzcholkow; j++) {
			temp[j] = 0;
		}
		macierzDijkstra[i] = temp;
	}
	for (int i = 0; i < tablicaDikstra.size(); i++) {
		if(tablicaDikstra[i].v1 != -1)
			macierzDijkstra[tablicaDikstra[i].v1][i] = tablicaDikstra[i].waga;
	}
}

void Dijkstra::dijkstraLista()
{
	int current = first;
	clearDijkstraList();
	for (int i = 0; i < liczbaWierzcholkow; i++) {
		sasiedzi nowysasiad;
		nowysasiad.visited = false;
		nowysasiad.v1 = liczbaWierzcholkow;
		nowysasiad.waga = -1;
		tablicaDikstra.push_back(nowysasiad);
	}
	tablicaDikstra[first].waga = 0;
	tablicaDikstra[first].v1 = -1;
	do {
		tablicaDikstra[current].visited = true;
		for (int i = 0; i < listaSasiadow[current].size(); i++) {
			if (listaSasiadow[current][i].v1 != first && (listaSasiadow[current][i].waga + tablicaDikstra[current].waga < tablicaDikstra[listaSasiadow[current][i].v1].waga || tablicaDikstra[listaSasiadow[current][i].v1].waga == -1)) {
				tablicaDikstra[listaSasiadow[current][i].v1].v1 = current;
				tablicaDikstra[listaSasiadow[current][i].v1].waga = listaSasiadow[current][i].waga + tablicaDikstra[current].waga;
			}
		}
		for (int i = 0; i < tablicaDikstra.size(); i++) {
			if (tablicaDikstra[i].waga > 0 && !tablicaDikstra[i].visited && tablicaDikstra[current].visited) {
				current = i;
			}
			else if (tablicaDikstra[i].waga < tablicaDikstra[current].waga && !tablicaDikstra[current].visited && tablicaDikstra[i].waga > 0 && !tablicaDikstra[i].visited) {
				current = i;
			}
		}
		if (tablicaDikstra[current].visited)
			for (int i = 0; i < tablicaDikstra.size(); i++) {
				if (!tablicaDikstra[i].visited && tablicaDikstra[current].visited) {
					current = i;
				}
				else if (!tablicaDikstra[i].visited && tablicaDikstra[i].waga < tablicaDikstra[current].waga) {
					current = i;
				}
			}
	} while (!tablicaDikstra[current].visited);
	for (int i = 0; i < liczbaWierzcholkow; i++) {
		vector<sasiedzi> nowySasiad;
		listaSasiadowDijkstra.push_back(nowySasiad);
	}
	for (int i = 0; i < tablicaDikstra.size(); i++) {
		sasiedzi nowysasiad;
		nowysasiad.waga = tablicaDikstra[i].waga;
		nowysasiad.visited = false;
		nowysasiad.v1 = i;
		if(i!=first)
			listaSasiadowDijkstra[tablicaDikstra[i].v1].push_back(nowysasiad);
	}
}

void Dijkstra::test()
{

}

void Dijkstra::displayDijkstraMacierz()
{
	cout << "MACIERZ SASIEDZTWA" << endl << " ";
	for (int i = 0; i < liczbaWierzcholkow; i++)
		cout << " " << i;
	for (int i = 0; i < liczbaWierzcholkow; i++) {
		cout << endl << i << " ";
		for (int j = 0; j < liczbaWierzcholkow; j++) {
			cout << macierzDijkstra[i][j] << " ";
		}
	}
}

void Dijkstra::displayDijkstraList()
{
	cout << endl << "LISTA SASIADOW";
	for (int i = 0; i < listaSasiadowDijkstra.size(); i++) {
		cout << endl << i;
		for (int j = 0; j < listaSasiadowDijkstra[i].size(); j++) {
			cout << " => " << listaSasiadowDijkstra[i][j].v1 << ":" << listaSasiadowDijkstra[i][j].waga;
		}
	}
}

void Dijkstra::clear()
{
	delete[]macierz;
	//delete macierz;
	listaSasiadow.clear();
}
