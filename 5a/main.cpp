
#include <iostream>
#include <limits.h>
#include "d_except.h"
#include <list>
#include <fstream>
#include "d_matrix.h"
#include <queue>
#include <vector>
#include <stack>

#include <boost/graph/adjacency_list.hpp>
#include "heapV.h"
//#include "disjointSetV.h"

#define LargeValue 99999999

using namespace std;
using namespace boost;

int const NONE = -1;  // Used to represent a node that does not exist

struct VertexProperties;
struct EdgeProperties;

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;

struct VertexProperties
{
   pair<int,int> cell; // maze cell (x,y) value
   Graph::vertex_descriptor pred;
   bool visited;
   bool marked;
   int weight;
};

// Create a struct to hold properties for each edge
struct EdgeProperties
{
   int weight;
   bool visited;
   bool marked;
};

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;
Graph::vertex_descriptor HasUnvistedAdjacentNode(Graph::vertex_descriptor v, Graph &g);
void clearVisited(Graph &g);
void DFT(Graph::vertex_descriptor start, Graph &g);
bool isConnected(Graph &g){
	clearVisited(g);
	Graph::vertex_descriptor start = 0;
	DFT(start, g);
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
	for (Graph::vertex_iterator vItr= vItrRange.first; vItr != vItrRange.second; ++vItr){
		if(!g[*vItr].visited){
			cout << *vItr;
			return false;
		}
	}
	return true;
}
void clearVisited(Graph &g)
{
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange;
	vItrRange = vertices(g);
	for (Graph::vertex_iterator vItr= vItrRange.first; vItr != vItrRange.second; ++vItr)
	{
		VertexProperties *v = &g[*vItr];
		v->visited = false;
	}
	pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(g);
	for (Graph::edge_iterator eItr= eItrRange.first; eItr != eItrRange.second; ++eItr)
	{
		EdgeProperties *e = &g[*eItr];
		e->visited = 0;
	}
}
Graph::vertex_descriptor HasUnvistedNode(Graph &g)
{
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
	for (Graph::vertex_iterator vItr= vItrRange.first; vItr != vItrRange.second; ++vItr) {
		if(!g[*vItr].visited)
		{
			return *vItr;
		}
	}
	return NONE;
}
void findSpanningForest(Graph &g, Graph &sf)
{
	clearVisited(g);
	while(HasUnvistedNode(g) != NONE) {
	Graph::vertex_descriptor start = HasUnvistedNode(g);
	g[start].visited = true;
	Graph::vertex_descriptor top;
	stack<Graph::vertex_descriptor> s;
	s.push(start);
	while(!s.empty()){
		top = s.top();
		Graph::vertex_descriptor next = HasUnvistedAdjacentNode(top, g);
		if(next != NONE){
			Graph::edge_descriptor e = edge(top, next, g).first;
			Graph::edge_descriptor e1 = add_edge(next, top, sf).first;
			Graph::edge_descriptor e2 = add_edge(top, next, sf).first;

			sf[e1].weight = g[e].weight;
			sf[e2].weight = g[e].weight;

			g[next].visited = true;
			s.push(next);
		}
		else{
			s.pop();
		}
	}
	}
}

bool isCyclic(Graph &g){
	clearVisited(g);
	queue<Graph::vertex_descriptor> q;
	Graph::vertex_descriptor v;
	Graph::vertex_descriptor start = 0;

	q.push(start);
	g[start].visited = true;

	while(!q.empty())
	{
		v = q.front();

		pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRange = adjacent_vertices(v, g);
		for (Graph::adjacency_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
		{
			if(!g[*vItr].visited)
			{
				g[*vItr].visited = true;
				g[*vItr].pred = v;
				q.push(*vItr);
			}
			else if(g[v].pred != *vItr && g[*vItr].pred != v){
				cout << *vItr << " " << v << " " << g[*vItr].pred;
				return true;
			}
		}
		q.pop();
	}
	return false;
}
int totalEdgeWeight(Graph &g){return 10;}

void initializeGraph(Graph &g,
                     Graph::vertex_descriptor &start,
                     Graph::vertex_descriptor &end, ifstream &fin)
// Initialize g using data from fin.  Set start and end equal
// to the start and end nodes.
{
   EdgeProperties e;

   int n, i, j;
   int startId, endId;
   fin >> n;
   fin >> startId >> endId;
   Graph::vertex_descriptor v;

   // Add nodes.
   for (int i = 0; i < n; i++)
   {
      v = add_vertex(g);
      if (i == startId)
         start = v;
      if (i == endId)
         end = v;
   }

   while (fin.peek() != '.')
   {
      fin >> i >> j >> e.weight;
      add_edge(i,j,e,g);
   }
}
Graph::vertex_descriptor HasUnvistedAdjacentNode(Graph::vertex_descriptor v, Graph &g)
{
	pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRange = adjacent_vertices(v, g);
	for (Graph::adjacency_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
	{
		if(!g[*vItr].visited)
		{
			return *vItr;
		}
	}
	return NONE;
}
void DFT(Graph::vertex_descriptor start, Graph &g){
	stack<Graph::vertex_descriptor> s;
	s.push(start);
	while(!s.empty()){
		Graph::vertex_descriptor top;
		top = s.top();

		Graph::vertex_descriptor next = HasUnvistedAdjacentNode(top, g);
		if(next != NONE){
			g[next].visited = true;
			s.push(next);
		}
		else{
			s.pop();
		}
	}
}
ostream &operator<<(ostream &ostr, const Graph &g)
{
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange;
	vItrRange = vertices(g);

	for (Graph::vertex_iterator vItr= vItrRange.first; vItr != vItrRange.second; ++vItr)
	{
		cout << *vItr << " ";
	}
	cout << endl;

	pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(g);
	for (Graph::edge_iterator eItr= eItrRange.first; eItr != eItrRange.second; ++eItr)
	{
		const EdgeProperties *edge = &g[*eItr];
		cout << source(*eItr, g) << " " << target(*eItr, g) << " ";
		ostr << " | Marked: " << edge->marked << " | Weight: " << edge->weight << " | Visited: " << edge->visited << endl;
	}
	return ostr;
}

int main()
{
   char x;
   ifstream fin;
   stack <int> moves;
   string fileName;

   // Read the name of the graph from the keyboard or
   // hard code it here for testing.

   fileName = "";

   cout << "Enter filename" << endl;
   cin >> fileName;

   fin.open(fileName.c_str());
   if (!fin)
   {
      cerr << "Cannot open " << fileName << endl;
      exit(1);
   }

   try

   {
      cout << "Reading graph" << endl;
      Graph g;

      Graph::vertex_descriptor start,end;

      initializeGraph(g,start,end,fin);
      cout << "Num nodes: " << num_vertices(g) << endl;
      cout << "Num edges: " << num_edges(g) << endl;
      cout << endl;

      // cout << g;

      bool connected;
      bool cyclic;

      cout << "Calling isCyclic" << endl;
      cyclic = isCyclic(g);

      if (cyclic)
         cout << "Graph contains a cycle" << endl;
      else
         cout << "Graph does not contain a cycle" << endl;

      cout << endl;

      cout << "Calling isConnected" << endl;
      connected = isConnected(g);

      if (connected)
         cout << "Graph is connected" << endl;
      else
         cout << "Graph is not connected" << endl;

      cout << endl;
      cout << "Finding spanning forest" << endl;

      // Initialize an empty graph to contain the spanning forest
      Graph sf(num_vertices(g));

      findSpanningForest(g,sf);
      cout << sf;
      cout << num_edges(sf);
      cout << "Spanning forest weight: " << totalEdgeWeight(sf)/2 << endl;
      cout << endl;

      cout << "Calling isConnected" << endl;
      connected = isConnected(sf);

      if (connected)
         cout << "Graph is connected" << endl;
      else
         cout << "Graph is not connected" << endl;
      cout << endl;

      cout << "Calling isCyclic" << endl;
      cyclic = isCyclic(sf);

      if (cyclic)
         cout << "Graph contains a cycle" << endl;
      else
         cout << "Graph does not contain a cycle" << endl;
      cout << endl;
   }
   catch (indexRangeError &ex)
   {
      cout << ex.what() << endl; exit(1);
   }
   catch (rangeError &ex)
   {
      cout << ex.what() << endl; exit(1);
   }
}

