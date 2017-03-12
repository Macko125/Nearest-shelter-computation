#include <iostream>
#include <fstream>
#include "NFGHeader.h"
#include "CNFGAlgorithm.h"
using namespace std; 

int main()
{
	CNFGAlgorithm algo;
	int vim, vert;
	algo.readDataFromFile("test.txt");
	algo.displayMatrix();
	algo.initDijkstra();
	cout << "enter vertex to damage" << endl;
	cin >> vim;
	algo.damageVertex(vim);
	cout << "enter last vertex to display" << endl;
	cin >> vert;
	algo.displayPath(vert);
	system("pause");
	return 0;
}