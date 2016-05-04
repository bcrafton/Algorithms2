//Project 5B
//main.cpp
//Oliver Scott + Brian Crafton

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
#include "graph.h"
#include "heapV.h"
//#include "disjointSetV.h"

#define LargeValue 99999999

using namespace std;
using namespace boost;

int const NONE = -1;  // Used to represent a node that does not exist
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
      BoostGraph::vertex_descriptor start, end;

      Graph g(start,end,fin);
	  cout << "Num nodes: " << g.getNumNodes() << endl;
	  cout << "Num edges: " << g.getNumEdges()/2 << endl;
      cout << endl;
      
      bool connected;
      bool cyclic;
      
	  cout << "\n --------- TEMPLATE GRAPH ---------- " << endl;
      cout << "Calling isCyclic" << endl;
      cyclic = g.isCyclic();
      
      if (cyclic)
         cout << "Graph contains a cycle" << endl;
      else
         cout << "Graph does not contain a cycle" << endl;
      
      cout << endl;
      
      cout << "Calling isConnected" << endl;
      connected = g.isConnected();
      
      if (connected)
         cout << "Graph is connected" << endl;
      else
         cout << "Graph is not connected" << endl;
      
      cout << endl;
      cout << "Finding spanning forest" << endl;
      
      // Initialize an empty graph to contain the spanning forest
	  Graph sf(g.getNumNodes());
	  Graph sf2(g.getNumNodes());
	  sf.findSpanningForrest(g);
	  sf2.msfPrim(g);
	  cout << "\n ---------------------------------------------------- "
		   << "\n ----------- OLD SPANNING FOREST RESULTS ------------ "
		   << "\n ---------------------------------------------------- " <<endl;
	  cout << "\nSpanning forest weight: " << sf.totalEdgeWeight()/2;
      
      cout << "\nCalling isConnected on spanning forest" << endl;
	  connected = sf.isConnected();
      
      if (connected)
         cout << "Graph is connected" << endl;
      else
         cout << "Graph is not connected" << endl;
      cout << endl;
      
      cout << "Calling isCyclic" << endl;
	  cyclic = sf.isCyclic();
      
      if (cyclic)
         cout << "Graph contains a cycle" << endl;
      else
         cout << "Graph does not contain a cycle" << endl;
      cout << endl;

	  int numNodes = sf.getNumNodes(),
		  numEdges = sf.getNumEdges()/2,
		  numTrees = numNodes - numEdges;
	  cout << "Num nodes: " << numNodes << endl;
	  cout << "Num edges: " <<  numEdges << endl;
	  cout << "Num trees: " << numTrees <<endl;

	  cout << "\n --------- GRAPH EDGES ---------- " << endl;
	  sf.printEdges();
	  cout << endl;

	  cout << "\n ---------------------------------------------------- "
		   << "\n --------- MSFPRIM SPANNING FOREST RESULTS ---------- "
		   << "\n ---------------------------------------------------- ";
	  cout << "\nSpanning Weight: " << sf2.totalEdgeWeight()/2;
	  
	  cout << "\nCalling isConnected on spanning forest" << endl;
	  bool connected2 = sf2.isConnected(); 

	  if (connected2)
         cout << "Graph is connected" << endl;
      else
         cout << "Graph is not connected" << endl;
      cout << endl;

	  cout << "Calling isCyclic" << endl;
	  bool cyclic2 = sf2.isCyclic();
	  if (cyclic2)
         cout << "Graph contains a cycle" << endl;
      else
         cout << "Graph does not contain a cycle" << endl;
      cout << endl;

	  numNodes = sf2.getNumNodes(),
	  numEdges = sf2.getNumEdges()/2,
	  numTrees = numNodes - numEdges;

	  cout << "Num nodes: " << numNodes << endl;
	  cout << "Num edges: " <<  numEdges << endl;
	  cout << "Num trees: " << numTrees <<endl;


	  cout << "\n --------- GRAPH EDGES ---------- " << endl;
	  sf2.printEdges();

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
   string pause;
   cin >> pause;
}

