#include "MST.h"
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <queue>
using namespace std;
void MST::loadFromFile(string fileName)
{
	//dodac czyszczenie dotychczasowego grafu
	ifstream read(fileName);
	string dane;
	read >> dane;
	liczbaKrawedzi = stoi(dane);
	read >> dane;
	liczbaWierzcholkow = stoi(dane);
	//vector<vector<int>> temp(vector<int>(liczbaWierzcholkow,0));
	//tworzenie kolejki priorytetowej krawedzi (kopiec)
	for (int i = 0; i < liczbaKrawedzi; i++) {
		Edge edge;
		read >> dane;
		edge.v0 = stoi(dane);
		read >> dane;
		edge.v1 = stoi(dane);
		read >> dane;
		edge.waga = stoi(dane);
		edges.push(edge);

	}
	read.close();
	/*while (!edges.empty()) {
		cout << edges.top().waga << " ";
		edges.pop();
	}*/
}

void MST::display()
{
}

void MST::generate(int liczbaWierzcholkow, int gestosc)
{
}

void MST::kruskal()
{
}

void MST::test()
{
}
