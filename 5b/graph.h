#pragma once
//graph.h
//Graph class to store and manipulate a boost graph
//Oliver Scott + Brian Crafton
#include <iostream>
#include <fstream>
#include <list>
#include <queue>
#include <stack>
#include <boost/graph/adjacency_list.hpp>
#include "heapV.h"

using namespace std;
using namespace boost;

struct VertexProperties;
struct EdgeProperties;
typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> BoostGraph;

#define LARGE_VAL 99999999

//* * * * * * * * * * * * * *
//* * * * DEFINITIONS * * * *
//* * * * * * * * * * * * * * 
struct VertexProperties
{
	pair<int,int> cell; // maze cell (x,y) value
	//BoostGraph::vertex_descriptor pred;
	adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties>::vertex_descriptor pred;
  	bool visited;
	bool marked;
	int weight;
};

//Create a struct to hold properties for each edge
struct EdgeProperties
{
	int weight;
	bool visited;
	bool marked;
};

class Graph
{
public:
	//Constructors, Setters, Getters
	Graph(int n);
	Graph(BoostGraph::vertex_descriptor &start, BoostGraph::vertex_descriptor &end, ifstream &fin);
	int getNumNodes();
	int getNumEdges();
	pair<BoostGraph::vertex_iterator, BoostGraph::vertex_iterator> getVertices();
	pair<BoostGraph::edge_iterator, BoostGraph::edge_iterator> getEdges();
	pair<BoostGraph::adjacency_iterator, BoostGraph::adjacency_iterator> getAdjVertices(BoostGraph::vertex_descriptor v);
	BoostGraph::edge_descriptor Graph::getEdgeDescriptor(BoostGraph::vertex_descriptor v, BoostGraph::vertex_descriptor u);
	void printEdges();
	
	//Generic Functions & Macros
	void clearVisited();
	void clearMarked();
	void setNodeWeights(int w);
	bool relax(BoostGraph::vertex_descriptor u, BoostGraph::vertex_descriptor v, BoostGraph::edge_descriptor fromUtoV);
	void printShortest(BoostGraph::vertex_descriptor start, BoostGraph::vertex_descriptor target);
	int totalEdgeWeight();
	stack<BoostGraph::vertex_descriptor> createStack(stack<BoostGraph::vertex_descriptor> &s, BoostGraph::vertex_descriptor start, BoostGraph::vertex_descriptor target);

	//Boolean-strict Functions & Macros
	bool isConnected();
	bool pathToAllWeight();
	bool pathToAllVisited();
	bool isCyclic();

	//Search based functions
	void BFS();
	void findSpanningForrest(Graph &g2);
	void msfPrim(Graph &g);
	void msfPrimLoop(Graph &g);
	bool bellmanFord(BoostGraph::vertex_descriptor s);
	bool dijstra(BoostGraph::vertex_descriptor start);
	void msfPrim(BoostGraph &g, BoostGraph &sf); /// OUT OF DATE

	//Path functions
	stack<BoostGraph::vertex_descriptor> findPathDFSRecursive(BoostGraph::vertex_descriptor start, BoostGraph::vertex_descriptor target, stack<BoostGraph::vertex_descriptor> &s);
	stack<BoostGraph::vertex_descriptor> findPathDFSStack(BoostGraph::vertex_descriptor start, BoostGraph::vertex_descriptor target);
	stack<BoostGraph::vertex_descriptor> findPathDFSShortest(BoostGraph::vertex_descriptor start, BoostGraph::vertex_descriptor target, stack<BoostGraph::vertex_descriptor> &s);
	stack<BoostGraph::vertex_descriptor> findPathBFS(BoostGraph::vertex_descriptor start, BoostGraph::vertex_descriptor target);
	
	//Overloads
	VertexProperties operator[](BoostGraph::vertex_descriptor v){return g[v];}
	EdgeProperties operator[](BoostGraph::edge_descriptor e){return g[e];}
private:
	adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> g;
};



