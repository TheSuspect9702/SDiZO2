#include "Dijkstra.h"
#include "Pomiary.h"
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <queue>
#include <algorithm>
using namespace std;
Pomiary pomiar1;

void Dijkstra::clearDijkstraMacierz()
{
	tablicaDikstra.clear();
	while (!kolejkaDikstra.empty())
		kolejkaDikstra.pop();
}

void Dijkstra::clearDijkstraList()
{
	tablicaDikstra.clear();
	while (!kolejkaDikstra.empty())
		kolejkaDikstra.pop();
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
	first = 0;
	liczbaWierzcholkow = liczbaWierzcholkow1;
	macierz = new int* [liczbaWierzcholkow];
	liczbaKrawedzi = liczbaWierzcholkow * (liczbaWierzcholkow - 1) * gestosc / 100;
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
	sasiedzi nowySasiad;
	value = rand() % liczbaWierzcholkow + 1;
	macierz[liczbaWierzcholkow - 1][0] = value;
	nowySasiad.v1 = 0;
	nowySasiad.waga = value;
	listaSasiadow[liczbaWierzcholkow-1].push_back(nowySasiad);
	pozostaleKrawedzie--;
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
				sasiedzi nowySasiad;
				nowySasiad.v1 = i;
				nowySasiad.waga = tablicaDikstra[i].waga;
				kolejkaDikstra.push(nowySasiad);
			}
		}
		while (kolejkaDikstra.size() > 0 && tablicaDikstra[kolejkaDikstra.top().v1].visited)
			kolejkaDikstra.pop();
		if (kolejkaDikstra.size() > 0)
			current = kolejkaDikstra.top().v1;
	} while (!tablicaDikstra[current].visited);
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
				sasiedzi nowySasiad;
				nowySasiad.v1 = listaSasiadow[current][i].v1;
				nowySasiad.waga = tablicaDikstra[listaSasiadow[current][i].v1].waga;
				kolejkaDikstra.push(nowySasiad);
			}

		}
		while (kolejkaDikstra.size() > 0 && tablicaDikstra[kolejkaDikstra.top().v1].visited)
			kolejkaDikstra.pop();
		if (kolejkaDikstra.size() > 0)
			current = kolejkaDikstra.top().v1;
		
	} while (!tablicaDikstra[current].visited);
}

void Dijkstra::test()
{
	double timeList = 0;
	double timeMacierz = 0;
	for (int i = 0; i < 100; i++) {
		generate(250, 20);
		pomiar1.StartCounter();
		dijkstraLista();
		timeList += pomiar1.GetCounter();
		pomiar1.StartCounter();
		dijkstraMacierz();
		timeMacierz += pomiar1.GetCounter();
	}
	cout << "\nSredni czas algorytmu dla listy: " << timeList * 10000;
	cout << "\nSredni czas algorytmu dla macierzy: " << timeMacierz * 10000;
}

void Dijkstra::displayDijkstraMacierz(int x)
{
	if (x == first)
		cout << "Wierzcholek: " << x << " koszt: - droga: - " << endl;
	else {
		cout << "Wierzcholek: " << x << " koszt: " << tablicaDikstra[x].waga << " droga: ";
		displayDijkstra(x);
		cout << endl;
	}
}

void Dijkstra::displayDijkstra(int x)
{
	if (x == first)
		cout << x;
	else {
		displayDijkstra(tablicaDikstra[x].v1);
		cout << " => " <<  x;
	}
}

void Dijkstra::clear()
{
	delete[]macierz;
	//delete macierz;
	listaSasiadow.clear();
}
