#include <iostream>
#include <fstream>
#include "NFGHeader.h"
#include "CNFGAlgorithm.h"
using namespace std; 

int main()
{
	CNFGAlgorithm algo;
	int vim = 0, vert = 0;
	algo.readDataFromFile("test.txt");
	algo.displayMatrix();
	algo.initDijkstra();

	while (vim <= 0)
	{
		cout << "enter vertex to damage" << endl;
		cin >> vim;
	}
	algo.damageVertex(vim-1);
	cout << "enter last vertex to display" << endl;
	while (vert < algo.getMatrixSize() + 1)
	{
		cin >> vert;
		algo.displayPath(vert-1);
	}
	system("pause");
	return 0;
}