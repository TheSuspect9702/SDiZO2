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
	bool operator<(const sasiedzi& other) const {
		return waga > other.waga;
	}
};
public:
	void loadFromFile(string fileName);
	void display();
	void generate(int liczbaWierzcholkow, int gestosc);
	void dijkstraMacierz();
	void dijkstraLista();
	void test();
	void displayDijkstraMacierz(int x);
	int liczbaWierzcholkow;
private:
	void clearDijkstraMacierz();
	void displayDijkstra(int x);
	void clearDijkstraList();
	priority_queue<sasiedzi> kolejkaDikstra;
	int** macierz;
	int liczbaKrawedzi;
	vector<vector<sasiedzi>> listaSasiadow;
	vector<sasiedzi> tablicaDikstra;
	void clear();
	int first;
};

