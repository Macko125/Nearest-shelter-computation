#include "CNFGAlgorithm.h"

CNFGAlgorithm::CNFGAlgorithm()
{
	m_adjMatrix = nullptr;
	m_matrixSize = 0;
}
CNFGAlgorithm::~CNFGAlgorithm() 
{
	if (m_adjMatrix != nullptr)
	{
		for (int i = 0; i < m_matrixSize; i++)
			delete m_adjMatrix[i];
		delete m_adjMatrix;
	}
}

void CNFGAlgorithm::deleteMatrix()
{
	if (m_adjMatrix != nullptr)
	{
		for (int i = 0; i < m_matrixSize; i++)
			delete m_adjMatrix[i];
		delete m_adjMatrix;
	}
	m_matrixSize = 0;
}
void CNFGAlgorithm::displayMatrix()
{
	for (int i = 0; i < m_matrixSize; i++)
	{
		for (int j = 0; j < m_matrixSize; j++)
		{
			cout << m_adjMatrix[i][j] << " ";
		}
		cout << endl;
	}
}

void CNFGAlgorithm::readDataFromFile(string filename)
{
	ifstream file;
	file.open(filename);
	if (!file.is_open())
	{
		cout << "error opening file" << endl;
		return;
	}

	string temp;
	getline(file, temp);
	if ((m_matrixSize = strtol(temp.c_str(), NULL, 10)) == 0)
	{
		cout << "error - wrong size value in config file" << endl;
		file.close();
		return;
	}
	if (m_matrixSize > 10000)
	{
		cout << "error - wrong size value in config file" << endl;
		m_matrixSize = 10000;
	}

	m_adjMatrix = new int*[m_matrixSize];
	for (int i = 0; i < m_matrixSize; i++)
		m_adjMatrix[i] = new int[m_matrixSize];

	for (int i = 0; i < m_matrixSize; i++)
	{
		for (int j = 0; j < m_matrixSize; j++)
		{
			if (file.eof())
				break;

			getline(file, temp, ';');
			m_adjMatrix[i][j] = strtol(temp.c_str(), NULL, 10);
		}
	}

	for (int i = 0; i < m_matrixSize; i++)
	{
		NFG_Vertex vertex;
		vertex.ID = i;
		for (int j = 0; j < m_matrixSize; j++)
		{
			if (m_adjMatrix[i][j] != 0)
				vertex.neighbour.push_back(sNeighbour(j, m_adjMatrix[i][j]));
		}
		m_NFG[i] = vertex;
	}

	while (!file.eof())
	{
		getline(file, temp, ';');
		if (isdigit(temp[temp.length() - 1]))
			rootVertices.push_back(strtol(temp.c_str(), NULL, 10));
	}

	for (auto root_id : rootVertices)
	{
		m_NFG[root_id].type = true;
		m_NFG[root_id].fastest_path.path_cost = 0;
		m_NFG[root_id].fastest_path.out_vertex = root_id;
	}
	file.close();
}

void CNFGAlgorithm::dijkstra()
{
	vector <int> Q; //vertex set
	map <int, NFG_Vertex> nfg_map;
	NFG_Vertex vert;
	nfg_map = m_NFG;
	map <int, bool> visited;
	for (auto root_id : rootVertices)
	{
		int root_id = rootVertices.back();
		while (!nfg_map.empty())
		{
			int min = max_path_cost + 1;
			int id = -1;
			for (auto v : m_NFG) // find vertex with lowest cost
			{
				if (v.second.fastest_path.path_cost < min && (nfg_map.find(v.second.ID) != nfg_map.end()))
				{
					id = v.second.ID;
					min = v.second.fastest_path.path_cost;
				}    // Node with the least distance will be selected first		remove u from Q
			}
			vert = m_NFG[id];
			nfg_map.erase(id);
	
			for (auto neighbour : vert.neighbour)
			{
				int alt = vert.fastest_path.path_cost + neighbour.edge_cost;
				if (alt < m_NFG[neighbour.id].fastest_path.path_cost)
				{
					m_NFG[neighbour.id].fastest_path.path_cost = alt;
					m_NFG[neighbour.id].fastest_path.out_vertex = id;
					m_NFG[id].fastest_path.in_vertices.push_back(neighbour.id);
					m_NFG[id].fastest_path.root_id = root_id;
					if (id == root_id)
						m_NFG[root_id].fastest_path.in_vertices.push_back(neighbour.id);
				}
			}
		}
	}
}

void CNFGAlgorithm::DNVRF(int vim_id, set<int> *Rim, set <int> *Dim)
{
	int vq = vim_id;
	Dim->insert(vim_id);
	vector<int> queue;
	queue.push_back(vim_id);
	while (!queue.empty())
	{
		vq = queue.back();
		queue.pop_back();
		for (auto vp : m_NFG[vq].neighbour)
		{
			if (find(m_NFG[vq].fastest_path.in_vertices.begin(), m_NFG[vq].fastest_path.in_vertices.end(), vp.id)
				!= m_NFG[vq].fastest_path.in_vertices.end())
			{
				queue.push_back(vp.id);
				Dim->insert(vp.id);
			}
			else if (vp.id != m_NFG[vq].fastest_path.out_vertex)
			{
				Rim->insert(vp.id);
			}
		}
	}
	for (auto iter : (*Dim))
	{
		int id = iter;
		if (Rim->find(id) != Rim->end())
		{
			Rim->erase(id);
		}
	}
}

