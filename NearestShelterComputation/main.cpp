#include <iostream>
#include <fstream>
#include "NFGHeader.h"
#include "CNFGAlgorithm.h"
using namespace std; 

int main()
{
	CNFGAlgorithm algo;
	algo.readDataFromFile("test.txt");
	algo.displayMatrix();
	algo.dijkstra();
	set <int> Rim;
	set <int> Dim;
	algo.DNVRF(5, &Rim, &Dim);

 	cout << "hello world" << endl;
	system("pause");
	return 0;
}