// Kruskal_MST.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct subSet {
	int parent;
	int rank;
};

class DisjointSet {
	subSet * s;
public:
	//constructor
	DisjointSet(int n)
	{
		s = new subSet[n];
		for (int i = 0; i < n; i++)
		{
			s[i].parent = i;
			s[i].rank = 0;
		}
	}
	//findSet---path compression
	int findSet(int i)
	{
		if (s[i].parent == i) return i;

		s[i].parent = findSet(s[i].parent);

		return s[i].parent;
	}
	//Union by rank
	void Union(int u, int v)
	{
		int uRoot = findSet(u);
		int vRoot = findSet(v);

		//Attach the smaller ranked tree to higher ranked tree
		if (s[uRoot].rank < s[vRoot].rank)
		{
			s[uRoot].parent = vRoot;
		}
		else if (s[uRoot].rank > s[vRoot].rank)
		{
			s[vRoot].parent = uRoot;
		}
		else //Same rank
		{
			s[vRoot].parent = uRoot;
			s[uRoot].rank++;
		}
	}
};

bool compareEdge(pair<pair<int, int>, int> A, pair<pair<int, int>, int> B)
{
	return A.second < B.second;
}

void Kruskal_MST(vector<vector<int> > &graph, int N)
{
	//First convert into Edges
	vector<pair<pair<int, int>, int> > Edges; //{(u, v), w}
	for (int i = 0; i < N; i++)
	{
		for (int j = i + 1; j < N; j++)
		{
			if (graph[i][j])
			{
				Edges.push_back(make_pair(make_pair(i, j), graph[i][j]));
			}
		}
	}

	//Now sort the edges..
	sort(Edges.begin(), Edges.end(), compareEdge);
	//create all vertices as DisjointSet
	DisjointSet ds(N);
	int total_dist = 0;
	//Now check all the edges
	for (int i = 0; i < Edges.size(); i++)
	{
		int u = Edges[i].first.first;
		int v = Edges[i].first.second;
		int w = Edges[i].second;

		if (ds.findSet(u) != ds.findSet(v))
		{
			// make this edge as part of the MST
			cout << u << " -> " << v << " : " << w << endl;
			total_dist += w;
			//Now make the union
			ds.Union(u, v);
		}
	}

	cout << "Kruskal MST : " << total_dist << endl;
}

int main()
{
	int N;
	cin >> N;

	vector<vector<int> > graph(N, vector<int>(N, 0));
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> graph[i][j];
		}
	}

	Kruskal_MST(graph, N);

    return 0;
}

