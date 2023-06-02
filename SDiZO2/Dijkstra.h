#pragma once
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
class Dijkstra
{
struct sasiedzi {
	int v1, waga;
};
public:
	int first;
	vector<int> visited;
	int waga;
	int** macierz;
	int** treeMatrix;
	int liczbaWierzcholkow;
	int liczbaKrawedzi;
	vector<vector<sasiedzi>> listaSasiadow;
	vector<sasiedzi> tablicaDikstra;
	void clearDijkstra();
	void loadFromFile(string fileName);
	void display();
	void generate(int liczbaWierzcholkow, int gestosc);
	void dijkstraMacierz();
	void dijkstraLista();
	void test();
	void clear();
};

