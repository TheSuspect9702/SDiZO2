#include "Dijkstra.h"
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <queue>
#include <algorithm>
using namespace std;


void Dijkstra::clearDijkstra()
{
	tablicaDikstra.clear();
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

void Dijkstra::generate(int liczbaWierzcholkow, int gestosc)
{

}

void Dijkstra::dijkstraMacierz()
{
	clearDijkstra();
	sasiedzi nowysasiad;
	nowysasiad.v1 = liczbaWierzcholkow;
	nowysasiad.waga = -1;
	for (int i = 0; i < liczbaWierzcholkow; i++) {
		sasiedzi nowysasiad;
		nowysasiad.v1 = liczbaWierzcholkow;
		nowysasiad.waga = -1;
		tablicaDikstra.push_back(nowysasiad);
	}
	tablicaDikstra[first].waga = 0;
	tablicaDikstra[first].v1 = -1;

}

void Dijkstra::dijkstraLista()
{
	clearDijkstra();

}

void Dijkstra::test()
{

}

void Dijkstra::clear()
{
	delete[]macierz;
	//delete macierz;
	listaSasiadow.clear();
}
