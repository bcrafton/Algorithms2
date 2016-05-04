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
//#include "heapV.h"

using namespace boost;
using namespace std;

struct VertexProperties;
struct EdgeProperties;

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;

// typedef property<edge_weight_t, int> EdgeProperty;

#define LargeValue 99999999

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
   

int main()
{
   try
   {
      ifstream fin;

      // Read the maze from the file.
      string fileName = "maze1.txt";
      
      fin.open(fileName.c_str());
      if (!fin)
      {
         cerr << "Cannot open " << fileName << endl;
         exit(1);
      }

      maze m(fin);
      fin.close();
      
      m.print(m.numRows()-1,m.numCols()-1,0,0);

      Graph g;
      m.mapMazeToGraph(g);

      //cout << g << endl;

      stack<Graph::vertex_descriptor> s;
      m.printVmap();
      clearVisited(g);

      stack<Graph::vertex_descriptor> s1;
      s1 = m.findShortestPathDFS(0,31,g,s1).first;
      printStack(s1);
   }
   catch(baseException &e){}
}
