/**
 * maze.h
 * Brian Crafton and Oliver Scott
 * The maze object for storing the maze
 *
 */

#include <vector>
#include <stack>
#include "d_except.h"
#include "d_matrix.h"
#include <iostream>
#include <limits.h>
#include <vector>
#include <list>
#include <fstream>
#include <queue>
#include <boost/graph/adjacency_list.hpp>
//#include "heapV.h"

#define BLOCKED -1
#define NIL -1

using namespace boost;
using namespace std;

struct VertexProperties;
struct EdgeProperties;

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;
void printVmap(matrix<Graph::vertex_descriptor> &vMap);
void setNewEdge(pair<Graph::edge_descriptor, bool> &e, Graph &g);

struct VertexProperties
{
   pair<int,int> cell; // maze cell (x,y) value
   Graph::vertex_descriptor pred;
   bool visited;
   bool marked;
   int weight;
};

typedef struct VertexProperties VertexProperties;

// Create a struct to hold properties for each edge
struct EdgeProperties
{
   int weight;
   bool visited;
   bool marked;
};

typedef struct EdgeProperties EdgeProperties;

// typedef property<edge_weight_t, int> EdgeProperty;

#define LargeValue 99999999

ostream &operator<<(ostream &ostr, const Graph &g);
ostream &operator<<(ostream &ostr, const VertexProperties &v);
ostream &operator<<(ostream &ostr, const EdgeProperties &e);
class maze
{
public:
   maze(ifstream &fin);
   void print(int,int,int,int);
   bool isLegal(int i, int j);
   void mapMazeToGraph(Graph &g);
   void printPath(Graph::vertex_descriptor end, stack<Graph::vertex_descriptor> &s, Graph g);
   int numRows(){return rows;};
   int numCols(){return cols;};

   bool findPathDFSRecursive(Graph::vertex_descriptor current, Graph::vertex_descriptor target, Graph &g, stack<Graph::vertex_descriptor> &s);
   stack<Graph::vertex_descriptor> findPathDFSStack(Graph::vertex_descriptor start, Graph::vertex_descriptor target, Graph &g);
   void findShortestPathBFS(Graph::vertex_descriptor start, Graph::vertex_descriptor target, Graph &g);
   pair<stack<Graph::vertex_descriptor>, bool> maze::findShortestPathDFS(Graph::vertex_descriptor current, Graph::vertex_descriptor target, Graph &g, stack<Graph::vertex_descriptor> s);

   void test(Graph &g);
   void printVmap();

private:
   int rows; // number of rows in the maze
   int cols; // number of columns in the maze12 a
   
   matrix<bool> value;
   matrix<Graph::vertex_descriptor> vMap;
};

maze::maze(ifstream &fin)
// Initializes a maze by reading values from fin.  Assumes that the
// number of rows and columns indicated in the file are correct.
{
   fin >> rows;
   fin >> cols;
   
   char x;
   
   value.resize(rows,cols);
   for (int i = 0; i <= rows-1; i++)
      for (int j = 0; j <= cols-1; j++)
      {
         fin >> x;
         if (x == 'O')
            value[i][j] = true;
         else
            value[i][j] = false;
      }
   
   vMap.resize(rows,cols);
}

void maze::print(int goalI, int goalJ, int currI, int currJ)
// Print out a maze, with the goal and current cells marked on the
// board.
{
   cout << endl;

   if (goalI < 0 || goalI > rows || goalJ < 0 || goalJ > cols)
      throw rangeError("Bad value in maze::print");

   if (currI < 0 || currI > rows || currJ < 0 || currJ > cols)
      throw rangeError("Bad value in maze::print");

   for (int i = 0; i <= rows-1; i++)
   {
      for (int j = 0; j <= cols-1; j++)
      {
	 if (i == goalI && j == goalJ)
	    cout << "*";
	 else
	    if (i == currI && j == currJ)
	       cout << "+";
	    else
	       if (value[i][j])
		  cout << " ";
	       else
		  cout << "X";	  
      }
      cout << endl;
   }
   cout << endl;
}

bool maze::isLegal(int i, int j)
// Return the value stored at the (i,j) entry in the maze, indicating
// whether it is legal to go to cell (i,j).
{
   if (i < 0 || i > rows || j < 0 || j > cols)
      throw rangeError("Bad value in maze::isLegal");

   return value[i][j];
}

void maze::mapMazeToGraph(Graph &g)
{
	const int rowCount = value.getRowCount();
	const int columnCount = value.getColumnCount();

	for(int rowCounter = 0; rowCounter < rowCount; rowCounter++){
		for(int columnCounter = 0; columnCounter < columnCount; columnCounter++){
			if(value[rowCounter][columnCounter]){
				int v = add_vertex(g);
				VertexProperties* vertex = &g[v];

				vertex->cell.first = rowCounter;
				vertex->cell.second = columnCounter;

				vertex->visited = false;
				vertex->weight = 0;
				vertex->marked = false;

				vMap[rowCounter][columnCounter] = v;

			}
			else{
				vMap[rowCounter][columnCounter] = BLOCKED;
			}
		}
	}

	int vertexNumber = 0;
	for(int rowCounter = 0; rowCounter < rowCount; rowCounter++){
			for(int columnCounter = 0; columnCounter < columnCount; columnCounter++){

				vertexNumber = rowCounter * columnCount + columnCounter;

				if(vertexNumber / columnCount > 0 && vMap[rowCounter][columnCounter] != BLOCKED && vMap[rowCounter-1][columnCounter] != BLOCKED){
					pair<Graph::edge_descriptor, bool> e = add_edge(vMap[rowCounter][columnCounter], vMap[rowCounter-1][columnCounter], g);
					setNewEdge(e, g);
				}
				if(vertexNumber/columnCount < rowCount-1 && vMap[rowCounter][columnCounter] != BLOCKED && vMap[rowCounter+1][columnCounter] != BLOCKED){
					pair<Graph::edge_descriptor, bool> e = add_edge(vMap[rowCounter][columnCounter], vMap[rowCounter+1][columnCounter], g);
					setNewEdge(e, g);
				}
				if(vertexNumber%columnCount > 0 && vMap[rowCounter][columnCounter] != BLOCKED && vMap[rowCounter][columnCounter-1] != BLOCKED){
					pair<Graph::edge_descriptor, bool> e = add_edge(vMap[rowCounter][columnCounter], vMap[rowCounter][columnCounter-1], g);
					setNewEdge(e, g);
				}
				if(vertexNumber%columnCount < columnCount-1 && vMap[rowCounter][columnCounter] != BLOCKED && vMap[rowCounter][columnCounter+1] != BLOCKED){
					pair<Graph::edge_descriptor, bool> e = add_edge(vMap[rowCounter][columnCounter], vMap[rowCounter][columnCounter+1], g);
					setNewEdge(e, g);
				}
			}
	}
}

void setNewEdge(pair<Graph::edge_descriptor, bool> &e, Graph &g)
{
	g[e.first].marked = false;
	g[e.first].weight = 0;
	g[e.first].visited = false;
}


void maze::printVmap()
{
	cout << endl;
	for(int rowCounter = 0; rowCounter < vMap.getRowCount(); rowCounter++){
				for(int columnCounter = 0; columnCounter < vMap.getColumnCount(); columnCounter++){
					if(vMap[rowCounter][columnCounter] == 4294967295)
						cout << "xx|";
					else if(vMap[rowCounter][columnCounter] < 10)
						cout << "0" << vMap[rowCounter][columnCounter] << "|";
					else
						cout << vMap[rowCounter][columnCounter] << "|";
				}
				cout << endl;
	}
}


void maze::test(Graph &g)
{
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange;
	vItrRange = vertices(g);

}

// Create a graph g that represents the legal moves in the maze m.
void maze::printPath(Graph::vertex_descriptor end,
                     stack<Graph::vertex_descriptor> &s,
                     Graph g)
{
	Graph::vertex_descriptor nextV = s.top();
	while(nextV != end)
	{
		print(rows-1, cols-1, g[nextV].cell.first, g[nextV].cell.second);
		cin.get();
		s.pop();
		nextV = s.top();
	}
}

bool maze::findPathDFSRecursive(Graph::vertex_descriptor current, Graph::vertex_descriptor target, Graph &g, stack<Graph::vertex_descriptor> &s)
{
	pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRange = adjacent_vertices(current, g);

	g[current].visited = true;

	if(current == target)
	{
		s.push(current);
		cout << g[current];
		return true;
	}
	else
	{
		for (Graph::adjacency_iterator vItr= vItrRange.first; vItr != vItrRange.second; ++vItr)
		{
			if(!g[*vItr].visited)
			{
				if(findPathDFSRecursive(*vItr, target, g, s))
				{
					s.push(current);
					cout << g[current];
					return true;
				}
			}
		}
		return false;
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
	return NIL;
}

stack<Graph::vertex_descriptor> maze::findPathDFSStack(Graph::vertex_descriptor start, Graph::vertex_descriptor target, Graph &g)
{
	stack<Graph::vertex_descriptor> s;

	s.push(start);

	while(!s.empty())
	{
		Graph::vertex_descriptor top;
		top = s.top();

		if(top == target)
		{
			return s;
		}


		Graph::vertex_descriptor next = HasUnvistedAdjacentNode(top, g);
		if(next != NIL)
		{
			g[next].visited = true;
			s.push(next);
		}
		else
		{
			s.pop();
		}
	}
	return s;
}

void maze::findShortestPathBFS(Graph::vertex_descriptor start, Graph::vertex_descriptor target, Graph &g)
{
	queue<Graph::vertex_descriptor> q;
	Graph::vertex_descriptor v;

	q.push(start);
	g[start].visited = true;

	while(!q.empty())
	{
		v = q.front();

		if(v == target)
		{
			return;
		}

		pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRange = adjacent_vertices(v, g);
		for (Graph::adjacency_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
		{
			if(!g[*vItr].visited)
			{
				g[*vItr].visited = true;
				q.push(*vItr);
			}
		}
		q.pop();
	}
}

void printStack(stack<Graph::vertex_descriptor> s)
{
	while(!s.empty())
	{
		cout << s.top() << endl;
		s.pop();
	}
}
stack<Graph::vertex_descriptor> copyStack(stack<Graph::vertex_descriptor> s)
{
	stack<Graph::vertex_descriptor> temp, copy;
	while(!s.empty())
	{
		temp.push(s.top());
		s.pop();
	}
	while(!temp.empty())
	{
		copy.push(temp.top());
		s.push(temp.top());
		temp.pop();
	}
	return copy;
}
pair<stack<Graph::vertex_descriptor>, bool> maze::findShortestPathDFS(Graph::vertex_descriptor current, Graph::vertex_descriptor target, Graph &g, stack<Graph::vertex_descriptor> s)
{
	bool foundPath = false;
	stack<Graph::vertex_descriptor> shortestPath;
	pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRange = adjacent_vertices(current, g);


	cout << "------------------------\n";
	cout << g[current];
	cout << s.size() << endl;
	cout << "------------------------\n";

	g[current].visited = true;
	s.push(current);


	if(current == target)
	{
		pair<stack<Graph::vertex_descriptor>, bool> p;
		p.first = s; // return this path.
		p.second = true;
		g[current].visited = false;
		return p;
	}
	else
	{
		for (Graph::adjacency_iterator vItr= vItrRange.first; vItr != vItrRange.second; ++vItr)
		{
			if(!g[*vItr].visited)
			{
				pair<stack<Graph::vertex_descriptor>, bool> p = findShortestPathDFS(*vItr, target, g, s);

				if(p.second)
				{
					if(!foundPath || p.first.size() < s.size())
					{
						shortestPath = p.first; // set shortest path to found path if it is shortest
						foundPath = true;
					}
				}
			}
		}
		g[current].visited = false;

		if(foundPath)
		{
			pair<stack<Graph::vertex_descriptor>, bool> p;
			p.first = shortestPath; // return the shortest path after checking all vertices.
			p.second = true;
			return p;
		}
		else
		{
			pair<stack<Graph::vertex_descriptor>, bool> p;
			p.first = shortestPath;
			p.second = false;
			return p;
		}
	}
}

// use iterator  here. ah the problem may have been num_vertices.
ostream &operator<<(ostream &ostr, const Graph &g)
{
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange;
	vItrRange = vertices(g);

	for (Graph::vertex_iterator vItr= vItrRange.first; vItr != vItrRange.second; ++vItr)
	{
		cout << g[*vItr];
	}

	pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(g);
	for (Graph::edge_iterator eItr= eItrRange.first; eItr != eItrRange.second; ++eItr)
	{
		const EdgeProperties *edge = &g[*eItr];
		ostr << "Edge: v1: (" << g[source(*eItr, g)].cell.first << ", "<< g[source(*eItr, g)].cell.second <<") ";
		ostr << "v2: (" << g[target(*eItr, g)].cell.first << ", "<< g[target(*eItr, g)].cell.second <<") ";
		ostr << " | Marked: " << edge->marked << " | Weight: " << edge->weight << " | Visited: " << edge->visited << endl;
	}
	return ostr;
}

ostream &operator<<(ostream &ostr, const VertexProperties &v)
{
	const VertexProperties *vertex = &v;
	ostr << "Vertex: " << "(" << vertex->cell.first << ", " << vertex->cell.second << ")";
	ostr << " | Marked: " << vertex->marked << " | Weight: " << vertex->weight << " | Visited: " << vertex->visited << endl;
	return ostr;
}

ostream &operator<<(ostream &ostr, const EdgeProperties &e)
{
	const EdgeProperties *edge = &e;
	cout << "Edge: " ;
	//ostr << "Edge: v1: (" << edge->p.first->cell.first << ", " << edge->p.first->cell.second << ")";
	ostr << " | Marked: " << edge->marked << " | Weight: " << edge->weight << " | Visited: " << edge->visited << endl;
	return ostr;
}
