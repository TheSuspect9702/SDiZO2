#pragma once
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Edge {
	int v0, v1, waga;
	//umozliwienie stworzenia kolejki malejacej
	bool operator<(const Edge& other) const {
		return waga > other.waga;
	}
};
struct sasiedzi {
	int v1, waga;
};
class MST
	
{
public:
	
	int waga;
	int liczbaWierzcholkow;
	int liczbaKrawedzi;
	void loadFromFile(string fileName);
	void display();
	void generate(int liczbaWierzcholkow, int gestosc);
	void primMacierz();
	void primLista();
	void test();
	int** treeMatrix;
	vector<vector<sasiedzi>> treeList;
	
private:
	void clearTreeMatrix();
	void clearTreeList();
	void clear();
	priority_queue<Edge> edges;
	int** macierz;
	vector<vector<sasiedzi>> listaSasiadow;
	vector<int> visited;
};

