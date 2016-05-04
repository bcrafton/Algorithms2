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

using namespace boost;
using namespace std;

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

typedef struct VertexProperties VertexProperties;

// Create a struct to hold properties for each edge
struct EdgeProperties
{
   pair<VertexProperties*, VertexProperties*> p;
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

   void makeVertices(Graph &g);

   void addAdjacentUp(Graph &g, int columnCount, int vertexNumber);
   void addAdjacentDown(Graph &g, int columnCount, int vertexNumber);
   void addAdjacentLeft(Graph &g, int columnCount, int vertexNumber);
   void addAdjacentRight(Graph &g, int columnCount, int vertexNumber);

   void test(Graph &g);

private:
   int rows; // number of rows in the maze
   int cols; // number of columns in the maze12 a
   
   matrix<bool> value;
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
   
   //vMap.resize(rows,cols);
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

void maze::makeVertices(Graph &g)
{
	const int rowCount = value.getRowCount();
	const int columnCount = value.getColumnCount();

	for(int rowCounter = 0; rowCounter < rowCount; rowCounter++){
		for(int columnCounter = 0; columnCounter < columnCount; columnCounter++)
		{
			int v = add_vertex(g);
			VertexProperties* vertex = &g[v];

			vertex->cell.first = rowCounter;
			vertex->cell.second = columnCounter;

			vertex->visited = false;
			vertex->weight = 0;

			if(value[rowCounter][columnCounter])
			{
				vertex->marked = false;
			}
			else
			{
				vertex->marked = true;
			}
		}
	}
}

void maze::mapMazeToGraph(Graph &g)
{
	makeVertices(g);
	const int rowCount = value.getRowCount();
	const int columnCount = value.getColumnCount();
	const int vertexCount = g.m_vertices.size();

	bool up, down, left, right;

	int vertexNumber;
	VertexProperties* vertex;

	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange;
	vItrRange = vertices(g);
	for (Graph::vertex_iterator vItr= vItrRange.first; vItr != vItrRange.second; ++vItr)
	{
		// to point to the vectors in the graph because graph iterators terribly documented.
		vertex = &g[*vItr];
		/* check to see if it is possible to have an edge in each direction
			OOO 123
			OOO	456
			OOO 789
			so 1 can only have an edge with 2,4, and 5
			so boolean values for (up, down, left, right) will be used
			1(left, up) = false
			1(right, down) = true

			5(all) = true

			9(left, up) = true
			9(right, down) = false
		*/
		vertexNumber = vertex->cell.first * columnCount + vertex->cell.second;
		if(!vertex->marked)
		{
			//up
			if(vertexNumber/columnCount > 0){
				up = true;
			}
			else{
				up = false;
			}
			//down
			if(vertexNumber/columnCount < rowCount-1){
				down = true;
			}
			else{
				down = false;
			}
			//left
			if(vertexNumber%columnCount > 0) {
				left = true;
			}
			else{
				left = false;
			}
			//right
			if(vertexNumber%columnCount < columnCount-1){
				right = true;
			}
			else{
				right = false;
			}

			if(up){
				addAdjacentUp(g, columnCount, vertexNumber);
			}
			if(down){
				addAdjacentDown(g, columnCount, vertexNumber);
			}
			if(left){
				addAdjacentLeft(g, rowCount, vertexNumber);
			}
			if(right){
				addAdjacentRight(g, rowCount, vertexNumber);
			}
		}
	}
}

void maze::test(Graph &g)
{
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange;
	vItrRange = vertices(g);
}

void maze::addAdjacentUp(Graph &g, int columnCount, int vertexNumber)
{
	int up_vertex = vertexNumber - columnCount;
	if(!g[up_vertex].marked){
		pair<Graph::edge_descriptor, bool> newEdge;

		newEdge = add_edge(vertexNumber, up_vertex, g);
		if(newEdge.second)
		{
			g[newEdge.first].visited = false;
			g[newEdge.first].marked = false;
			g[newEdge.first].weight = 0;
			g[newEdge.first].p.first = &g[vertexNumber];
			g[newEdge.first].p.second = &g[up_vertex];
		}
	}
}

void maze::addAdjacentDown(Graph &g, int columnCount, int vertexNumber)
{
	int down_vertex = vertexNumber + columnCount;
	if(!g[down_vertex].marked){
		pair<Graph::edge_descriptor, bool> newEdge;

		newEdge = add_edge(vertexNumber, down_vertex, g);
		if(newEdge.second)
		{
			g[newEdge.first].visited = false;
			g[newEdge.first].marked = false;
			g[newEdge.first].weight = 0;
			g[newEdge.first].p.first = &g[vertexNumber];
			g[newEdge.first].p.second = &g[down_vertex];
		}
	}
}

void maze::addAdjacentLeft(Graph &g, int rowCount, int vertexNumber)
{
	int left_vertex = vertexNumber--;
	if(!g[left_vertex].marked){
		pair<Graph::edge_descriptor, bool> newEdge;

		newEdge = add_edge(vertexNumber, left_vertex, g);
		if(newEdge.second)
		{
			g[newEdge.first].visited = false;
			g[newEdge.first].marked = false;
			g[newEdge.first].weight = 0;
			g[newEdge.first].p.first = &g[vertexNumber];
			g[newEdge.first].p.second = &g[left_vertex];
		}
	}
}

void maze::addAdjacentRight(Graph &g, int rowCount, int vertexNumber)
{
	int right_vertex = vertexNumber++;
	if(!g[right_vertex].marked){
		pair<Graph::edge_descriptor, bool> newEdge;

		newEdge = add_edge(vertexNumber, right_vertex, g);
		if(newEdge.second)
		{
			g[newEdge.first].visited = false;
			g[newEdge.first].marked = false;
			g[newEdge.first].weight = 0;
			g[newEdge.first].p.first = &g[vertexNumber];
			g[newEdge.first].p.second = &g[right_vertex];
		}
	}
}

// Create a graph g that represents the legal moves in the maze m.
void maze::printPath(Graph::vertex_descriptor end, stack<Graph::vertex_descriptor> &s, Graph g)
{
	while(s.top() != end)
	{
		cout << g[s.top()];
		s.pop();
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
		cout << g[*eItr];
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
	ostr << "Edge: v1: (" << edge->p.first->cell.first << ", " << edge->p.first->cell.second << ")";
	ostr << " v2: (" << edge->p.second->cell.first << ", " << edge->p.second->cell.second << ")";
	ostr << " | Marked: " << edge->marked << " | Weight: " << edge->weight << " | Visited: " << edge->visited << endl;
	return ostr;
}
