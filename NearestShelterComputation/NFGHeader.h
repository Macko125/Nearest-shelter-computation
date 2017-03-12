#pragma once
#include <vector>
#include <map>

static int const max_path_cost = 0x0FFFFFFF - 1;

struct sNeighbour
{
	int id;
	int edge_cost;
	sNeighbour(int id, int edge_cost) :
		id(id),
		edge_cost (edge_cost)
	{}
	//operator == check if ids are equal
	bool operator==(const sNeighbour& other)
	{
		if (this->id == other.id)
			return true;
		else 
			return false;
	}
};

struct sFastestPath
{
	int root_id;
	long long path_cost;
	int out_vertex;
	std::vector <int> in_vertices;
	sFastestPath()
	{
		root_id = 0;
		path_cost = max_path_cost;
		out_vertex = max_path_cost; //undef vertex
	}
};

struct NFG_Vertex
{
	int ID;
	bool type; // 0 - general vertex, 1 - root
	sFastestPath fastest_path;
	std::vector <sNeighbour> neighbour;
	NFG_Vertex()
	{
		ID = 0;
		type = 0;
	}
};
