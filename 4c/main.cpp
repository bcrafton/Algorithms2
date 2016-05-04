/**
 * Project 4a
 * main.cpp
 * Brian Crafton and Oliver Scott
 * the main function
 */

#include <iostream>
#include <limits.h>
#include <vector>
#include <list>
#include <fstream>
#include <queue>
#include "maze.h"

#include <boost/graph/adjacency_list.hpp>
#include "heapV.h"

using namespace boost;
using namespace std;

struct VertexProperties;
struct EdgeProperties;

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;

// typedef property<edge_weight_t, int> EdgeProperty;

#define LargeValue 99999999
#define NIL -1

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
      g[v].marked = false;
      g[v].visited = false;
      g[v].weight = 0;
      if (i == startId)
	 start = v;
      if (i == endId)
	 end = v;
   }

   while (fin.peek() != '.')
   {
      fin >> i >> j >> e.weight;
      e.marked = false;
      e.visited = false;
      add_edge(i,j,e,g);
   }
}

bool relax(Graph &g, int u, int v){
	Graph::vertex_descriptor v1 = u;
	Graph::vertex_descriptor v2 = v;

	Graph::edge_descriptor e = edge(v1, v2, g).first;
	if(g[v2].weight > g[v1].weight + g[e].weight)
	{
		g[v2].weight = g[v1].weight + g[e].weight;
		g[v2].pred = v1;
		return true;
	}
	return false;
}


// Mark all nodes in g as not visited.

void setNodeWeights(Graph &g, int w)
{
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange;
	vItrRange = vertices(g);
	for (Graph::vertex_iterator vItr= vItrRange.first; vItr != vItrRange.second; ++vItr)
	{
		VertexProperties *v = &g[*vItr];
		v->weight = 0;
	}
	pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(g);
	for (Graph::edge_iterator eItr= eItrRange.first; eItr != eItrRange.second; ++eItr)
	{
		EdgeProperties *e = &g[*eItr];
		e->weight = 0;
	}
}
// Set all node weights to w.

void clearMarked(Graph &g)
{
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange;
	vItrRange = vertices(g);
	for (Graph::vertex_iterator vItr= vItrRange.first; vItr != vItrRange.second; ++vItr)
	{
		VertexProperties *v = &g[*vItr];
		v->marked = false;
	}
	pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(g);
	for (Graph::edge_iterator eItr= eItrRange.first; eItr != eItrRange.second; ++eItr)
	{
		EdgeProperties *e = &g[*eItr];
		e->marked = 0;
	}
}

void unsetWeights(Graph &g)
{
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange;
	vItrRange = vertices(g);
	for (Graph::vertex_iterator vItr= vItrRange.first; vItr != vItrRange.second; ++vItr)
	{
		VertexProperties *v = &g[*vItr];
		v->weight = LargeValue;
	}
}

heapV<Graph::vertex_descriptor, Graph> createHeap(Graph &g)
{
	vector<Graph::vertex_descriptor> list;
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange;
	vItrRange = vertices(g);
	for (Graph::vertex_iterator vItr= vItrRange.first; vItr != vItrRange.second; ++vItr) {
		list.push_back(*vItr);
	}
	heapV<Graph::vertex_descriptor, Graph> h;
	h.initializeMinHeap(list, g);
	return h;
}

vector<Graph::vertex_descriptor> getPath(Graph::vertex_descriptor s, Graph::vertex_descriptor e, Graph &g)
{
	vector<Graph::vertex_descriptor> path;
	Graph::vertex_descriptor v = e;
	while(v != s)
	{
		path.insert(path.begin(), v);
		v = g[v].pred;
	}
	path.insert(path.begin(), v);
	return path;
}

void printPath(vector<Graph::vertex_descriptor> path)
{
	vector<Graph::vertex_descriptor>::iterator itr = path.begin();
	while(itr != path.end())
	{
		cout << "|" << *itr;
		itr++;
	}
	cout << "|" << endl;
}

bool BellmanFord(Graph &g, Graph::vertex_descriptor s)
{
	unsetWeights(g);
	g[s].weight = 0;
	clearVisited(g);

	heapV<Graph::vertex_descriptor, Graph> h = createHeap(g);

	Graph::vertex_descriptor v;
	const int vertexCount = num_vertices(g);
	for(int vertexCounter = 0; vertexCounter < vertexCount-1; vertexCounter++)
	{
		v = h.extractMinHeapMinimum(g);
		h.minHeapDecreaseKey(h.size()-1, g);

		pair<Graph::adjacency_iterator, Graph::adjacency_iterator> adjacentItrRange = adjacent_vertices(v, g);
		for (Graph::adjacency_iterator adjacentItr = adjacentItrRange.first; adjacentItr != adjacentItrRange.second; ++adjacentItr)
		{
			relax(g, v, *adjacentItr);
		}
	}

	Graph::vertex_descriptor v1, v2;
	pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(g);
	for (Graph::edge_iterator eItr= eItrRange.first; eItr != eItrRange.second; ++eItr)
	{
		v1 = source(*eItr, g);
		v2 = target(*eItr, g);

		if(g[v2].weight > g[v1].weight + g[*eItr].weight)
		{
			return false;
		}
	}
	return true;
}

void Dijkstra(Graph &g, Graph::vertex_descriptor s)
{
	unsetWeights(g);
	g[s].weight = 0;
	clearVisited(g);

	heapV<Graph::vertex_descriptor, Graph> h = createHeap(g);

	Graph::vertex_descriptor v;
	Graph::edge_descriptor e;
	while(h.size())
	{
		v = h.extractMinHeapMinimum(g);

		g[v].visited = true;
		pair<Graph::adjacency_iterator, Graph::adjacency_iterator> adjacentItrRange = adjacent_vertices(v, g);
		for (Graph::adjacency_iterator adjacentItr = adjacentItrRange.first; adjacentItr != adjacentItrRange.second; ++adjacentItr)
		{
			Graph::vertex_descriptor w = *adjacentItr;
			if(!g[w].visited)
				if(relax(g, v, w)){
					int index = h.getIndex(w);
					h.minHeapDecreaseKey(index, g);
				}
		}
	}
}

/*
Dijkstra(graph g, vertex start, vertex end)
{
	unvisit all nodes
	set shortest path(all nodes) = infinity
	set shortest path(start) = 0
	push all nodes into priority queue
	while(priority queue is not empty)
		pop node v off the priority queue
		visit v
		for(all unvisited neighbors w of v)
			sp[w] = min(sp[w], sp[v] + weight[v,w])
			if( this is now a new shortest path)
				set pred[w] = v
}
*/
int main()
{
   try
   {
      ifstream fin;
      cout << "Please enter the name of the file: " ;
      string fileName;
      cin >> fileName;

      fin.open(fileName.c_str());
      if (!fin)
      {
    	  cerr << "Cannot open " << fileName << endl;
          exit(1);
      }
      Graph g;
      Graph::vertex_descriptor start;
      Graph::vertex_descriptor end;
      initializeGraph(g, start, end, fin);

      cout << "-----BellmanFord-----" << endl;
      if(BellmanFord(g, 0))
      {
    	  cout << "Path Weight: "<< g[end].weight << ", ";
          printPath(getPath(start,end,g));
      }
      else
      {
    	  cout << "No path found" << endl;
      }
      cout << "----------" << endl;
      cout << "-----Dijkstra-----" << endl;
      Dijkstra(g, start);
      if(g[end].weight < LargeValue)
      {
    	  cout << "Path Weight: "<< g[end].weight << ", ";
    	  printPath(getPath(start,end,g));
      }
      else
      {
    	  cout << "No path found" << endl;
      }
      cout << "----------" << endl;
      fin.close();

   }
   catch(baseException &e){}
}
