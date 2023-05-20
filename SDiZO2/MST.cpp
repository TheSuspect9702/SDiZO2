#include "MST.h"
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <queue>
#include <algorithm>
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
	macierz = new int *[liczbaWierzcholkow];
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
	//najpierw tworze pusta strukture o zadanych parametrach
	// nastepnie wypelniam ja zgodnie z danymi z pliku 
	// na podstawie struktury tworze priorytetowa liste krawedzi 
	//vector<vector<int>> temp(vector<int>(liczbaWierzcholkow,0));
	//tworzenie kolejki priorytetowej krawedzi (kopiec)
	for (int i = 0; i < liczbaKrawedzi; i++) {
		sasiedzi nowysasiad;
		sasiedzi nowysasiad1;
		read >> dane;
		w1 = stoi(dane);
		read >> dane;
		w2 = stoi(dane);
		read >> dane;
		w = stoi(dane);
		nowysasiad.v1 = w2;
		nowysasiad.waga = w;
		nowysasiad1.v1 = w1;
		nowysasiad1.waga = w;
		macierz[w1][w2] = w;
		macierz[w2][w1] = w;
		listaSasiadow[w1].push_back(nowysasiad);
		listaSasiadow[w2].push_back(nowysasiad1);
		
	}
	read.close();
	
}

void MST::display()
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
		cout << endl << i << ": ";
		for (int j = 0; j < listaSasiadow[i].size(); j++) {
			cout << listaSasiadow[i][j].v1 << ":" << listaSasiadow[i][j].waga << " ";
		}
	}
}

void MST::generate(int liczbaWierzcholkow, int gestosc)
{
	liczbaWierzcholkow = liczbaWierzcholkow;
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
}

void MST::primMacierz()
{
	clearTree();
	treeMatrix = new int* [liczbaWierzcholkow];
	for (int i = 0; i < liczbaWierzcholkow; i++) {
		int* temp = new int[liczbaWierzcholkow];
		for (int j = 0; j < liczbaWierzcholkow; j++) {
			temp[j] = 0;
		}
		treeMatrix[i] = temp;
	}
	visited.push_back(0);
	cout << liczbaWierzcholkow << endl;
	while (visited.size() != liczbaWierzcholkow) {
		for (int i = 0; i < liczbaWierzcholkow; i++) {
			if (macierz[visited[visited.size() - 1]][i] != 0) {
				Edge edge;
				edge.v0 = visited[visited.size() - 1];
				edge.v1 = i;
				edge.waga = macierz[visited[visited.size() - 1]][i];
				edges.push(edge);
			}
		}
		while (count(visited.begin(), visited.end(), edges.top().v1) && count(visited.begin(), visited.end(), edges.top().v0))
			edges.pop();
		visited.push_back(edges.top().v1);
		waga += edges.top().waga;
		treeMatrix[edges.top().v1][edges.top().v0] = edges.top().waga;
		treeMatrix[edges.top().v0][edges.top().v1] = edges.top().waga;
		edges.pop();
	}
}

void MST::primLista()
{
	clearTree();
	for (int i = 0; i < liczbaWierzcholkow; i++) {
		vector<sasiedzi> nowySasiad;
		treeList.push_back(nowySasiad);
	}
	visited.push_back(0);
	while (visited.size() != liczbaWierzcholkow) {
		for (int i = 0; i < listaSasiadow[visited[visited.size()-1]].size(); i++) {
			Edge edge;
			edge.v0 = visited[visited.size() - 1];
			edge.v1 = listaSasiadow[visited[visited.size() - 1]][i].v1;
			edge.waga = listaSasiadow[visited[visited.size() - 1]][i].waga;
			edges.push(edge);
		}
		while (count(visited.begin(), visited.end(), edges.top().v1) && count(visited.begin(), visited.end(), edges.top().v0))
			edges.pop();
		visited.push_back(edges.top().v1);
		sasiedzi nowysasiad,nowysasiad1;
		nowysasiad.v1 = edges.top().v0;
		nowysasiad.waga = edges.top().waga;
		nowysasiad1.v1 = edges.top().v1;
		nowysasiad1.waga = edges.top().waga;
		treeList[edges.top().v0].push_back(nowysasiad1);
		treeList[edges.top().v1].push_back(nowysasiad);
		waga += edges.top().waga;
		edges.pop();

	}
}
void MST::test()
{

}

void MST::clearTree()
{
	delete treeMatrix;
	treeList.clear();
	while(edges.size() >0)
		edges.pop();
	visited.clear();
	waga = 0;
}


