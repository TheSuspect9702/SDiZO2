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
class MST
	
{
public:
	priority_queue<Edge> edges;
	int liczbaWierzcholkow;
	int liczbaKrawedzi;
	vector<vector<int>> macierzSasiedztwa;
	void loadFromFile(string fileName);
	void display();
	void generate(int liczbaWierzcholkow, int gestosc);
	void kruskal();
	void test();
};

