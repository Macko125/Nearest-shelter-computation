#pragma once
#ifndef _NFGALGORITHM
#define _NFGALGORITHM

#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <set>
#include "NFGHeader.h"
using namespace std;

class CNFGAlgorithm
{
public:
	void readDataFromFile (string filename);
	//void dijkstra (int root, int target);
	void dijkstra(vector <int> root_vertices, map <int, NFG_Vertex> *nfg, bool recalculation = false);
	void deleteMatrix();
	void displayMatrix();
	void initDijkstra();
	void displayPath(int vertex_id);
	void damageVertex(int vim);
	CNFGAlgorithm();
	~CNFGAlgorithm();
private:
	void DNVRF(int vim_id, set<int> *Rim, set <int> *Dim);
	void damageRangeReconstruction(set<int> *Rim, set <int> *Dim);
	std::map <int, NFG_Vertex> m_NFG;
	int **m_adjMatrix;
	int m_matrixSize;
	vector <int> rootVertices;
};

#endif