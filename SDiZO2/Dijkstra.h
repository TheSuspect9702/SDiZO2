#pragma once
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
class Dijkstra
{
struct sasiedzi {
	int v1, waga;
	bool visited;
};
public:
	void loadFromFile(string fileName);
	void display();
	void generate(int liczbaWierzcholkow, int gestosc);
	void dijkstraMacierz();
	void dijkstraLista();
	void test();
	void displayDijkstraMacierz();
	void displayDijkstraList();
private:
	void clearDijkstraMacierz();
	void clearDijkstraList();
	int** macierz;
	int** macierzDijkstra;
	int liczbaWierzcholkow;
	int liczbaKrawedzi;
	vector<vector<sasiedzi>> listaSasiadow;
	vector<vector<sasiedzi>> listaSasiadowDijkstra;
	vector<sasiedzi> tablicaDikstra;
	void clear();
	int first;
};

