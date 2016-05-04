//graph.cpp
//Definition of graph class functions
//Oliver Scott + Brian Crafton

#include "graph.h"

//* * * * * * * * * * * * * *
//* * GENERIC FUNCTIONS * * * 
//* * * * * * * * * * * * * * 
//printEdges
//The output for project 5B
void Graph::printEdges()
{
	pair<BoostGraph::edge_iterator, BoostGraph::edge_iterator> eItrRange = edges(g);
	int edgeCounter = 0;
	for(BoostGraph::edge_iterator eItr = eItrRange.first; eItr != eItrRange.second; eItr++)
	{
		edgeCounter++;
		BoostGraph::vertex_descriptor sourceV = source(*eItr, g);
		BoostGraph::vertex_descriptor targetV = target(*eItr, g);
		cout << "\nEdge " << edgeCounter << ":" 
			<< "\nSource: " << targetV << "  Target: " << sourceV;
	}
}
//clearVisited
//Sets all visited descriptions for each node to false
void Graph::clearVisited()
{
	// Mark all nodes in g as not visited.
	pair<BoostGraph::vertex_iterator, BoostGraph::vertex_iterator> vItrRange = vertices(g);
	for(BoostGraph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; vItr++)
	{
		g[*vItr].visited = false;
	}
}
//getNumEdges
//Returns number of edges in g
int Graph::getNumEdges()
{
	return num_edges(g);
}
//getNumNodes
//Returns number of nodes in 
int Graph::getNumNodes()
{
	return num_vertices(g);
}
//getVertices
//Returns vertex iterator pair for vertices
pair<BoostGraph::vertex_iterator, BoostGraph::vertex_iterator> Graph::getVertices()
{
	return vertices(g);
}
//getEdges
//Return edge iteror pair
pair<BoostGraph::edge_iterator, BoostGraph::edge_iterator> Graph::getEdges()
{
	return edges(g);
}
//getAdjEdges
//Returns vertex iterator pair for vertices
pair<BoostGraph::adjacency_iterator, BoostGraph::adjacency_iterator> Graph::getAdjVertices(BoostGraph::vertex_descriptor v)
{
	return adjacent_vertices(v, g);
}
//getEdgeDescriptor
//Returns edge descriptor for two vertices. Assumes Undirected.
BoostGraph::edge_descriptor Graph::getEdgeDescriptor(BoostGraph::vertex_descriptor v, BoostGraph::vertex_descriptor u)
{
	pair<BoostGraph::edge_descriptor, bool> thisEdge = edge(v, u, g);
	return  thisEdge.first;
}
//setNodeWeights
//Creates uniform node weights for all nodes in graph
void Graph::setNodeWeights(int w)
{
	// Set all node weights to w.
	pair<BoostGraph::vertex_iterator, BoostGraph::vertex_iterator> vItrRange = vertices(g);
	for(BoostGraph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; vItr++)
	{
		g[*vItr].weight = w;
	}
}
//clearMarked
//Sets all marked descriptions to false for each node
void Graph::clearMarked()
{
	pair<BoostGraph::vertex_iterator, BoostGraph::vertex_iterator> vItrRange = vertices(g);
	for(BoostGraph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; vItr++)
	{
		g[*vItr].marked = false;
	}
}
//relax
//Reduces the node weight value to a lesser value if a shorter path is found. Returns whether or not an update has been performed.
bool Graph::relax(BoostGraph::vertex_descriptor u, BoostGraph::vertex_descriptor v, BoostGraph::edge_descriptor fromUtoV)
{
	const int edgeWeight = g[fromUtoV].weight;
	if(g[v].weight > (g[u].weight + edgeWeight) )
	{
		g[v].weight = g[u].weight + edgeWeight;
		g[v].pred = u;
		return true;
	}
	else
		return false;
}
//pathToAllVisited
//Returns whether or not all nodes were reached using the visited reference flag.
bool Graph::pathToAllVisited()
{
	pair<BoostGraph::vertex_iterator, BoostGraph::vertex_iterator> vItrRange = vertices(g);
	for(BoostGraph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; vItr++)
	{
		if(!g[*vItr].visited)
			return false;
	}
	return true;
}
//pathToAllWeight
//Returns whether or not all nodes were reached in dijstra/bellford. References weight values as opposed to visit flag.
bool Graph::pathToAllWeight()
{
	pair<BoostGraph::vertex_iterator, BoostGraph::vertex_iterator> vItrRange = vertices(g);
	for(BoostGraph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; vItr++)
	{
		if(g[*vItr].weight == LARGE_VAL)
			return false;
	}
	return true;
}
//isConnected
//Returns whether every tree is connected in an undirected graph -- the advantage being only one start node needs to be checked. 
bool Graph::isConnected()
{
	this->BFS();
	return this->pathToAllVisited();
}
//isCyclic
//Returns whether or not the graph is cyclic
bool Graph::isCyclic()
{
	pair<BoostGraph::edge_iterator, BoostGraph::edge_iterator> eItrRange = edges(g);
	for(BoostGraph::edge_iterator eItr = eItrRange.first; eItr != eItrRange.second; eItr++)
	{
		BoostGraph::vertex_descriptor sourceV = source(*eItr, g);
		BoostGraph::vertex_descriptor targetV = target(*eItr, g);
		if( (g[targetV].pred != sourceV) && (g[sourceV].pred != targetV) )
			return true;
	}

	return false;
}
//printShortest
//Prints shortest path in node order
void Graph::printShortest(BoostGraph::vertex_descriptor start, BoostGraph::vertex_descriptor target)
{

	stack<BoostGraph::vertex_descriptor> s;
	BoostGraph::vertex_descriptor nextV = target;

	while(nextV != start)
	{
		s.push(nextV);
		nextV = g[nextV].pred;
	}
	s.push(start);

	while(!s.empty())
	{
		nextV = s.top();
		cout << "\nNode: " << nextV;
		s.pop();
	}
}
//totalEdgeWeight
//Returns total weight of edges.
int Graph::totalEdgeWeight()
{
	int w = 0;
	pair<BoostGraph::edge_iterator, BoostGraph::edge_iterator> eItrRange = edges(g);
	for(BoostGraph::edge_iterator eItr = eItrRange.first; eItr != eItrRange.second; eItr++)
	{
		w += g[*eItr].weight;
	}
	return w;
}

//* * * * * * * * * * * * * *
//* * CONSTRUCTORS * * ** * *
//* * * * * * * * * * * * * * 
//Constructor -- with n nodes
//Initializes a graph with n number of nodes.
Graph::Graph(int n)
{
	g = BoostGraph(n);
	this->clearVisited();
	this->clearMarked();
}
//Constructor -- from file
//Initializes graph given an input ifstream
Graph::Graph(BoostGraph::vertex_descriptor &start, BoostGraph::vertex_descriptor &end, ifstream &fin)
	// Initialize g using data from fin.  Set start and end equal
	// to the start and end nodes.
{
	EdgeProperties e;

	int n, i, j;
	int startId, endId;
	fin >> n;
	fin >> startId >> endId;
	BoostGraph::vertex_descriptor v;

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
//findSpanningForrest
//Given a blueprint graph of possible edges -- generates a forrest of a connected path
void Graph::findSpanningForrest(Graph &g2)
{
	pair<BoostGraph::vertex_iterator, BoostGraph::vertex_iterator> vItrRange = this->getVertices();
	BoostGraph::vertex_iterator start = vItrRange.first;

	while(g[*start].visited) //Use first unvisited vertext for beginning of tree. This will allow the call back to findSpanningForrest to create a forrest   
	{
		start++;
		if(start == vItrRange.second)
			return;
	}

	g[*start].visited = true;
	queue<BoostGraph::vertex_descriptor> q;
	q.push(*start);

	while(!q.empty())
	{
		BoostGraph::vertex_descriptor currV = q.front();
		pair<BoostGraph::adjacency_iterator, BoostGraph::adjacency_iterator> adjItrRange = g2.getAdjVertices(currV);
		for(BoostGraph::adjacency_iterator adjItr = adjItrRange.first; adjItr != adjItrRange.second; adjItr++)
		{
			if(!g[*adjItr].visited)
			{
				BoostGraph::edge_descriptor currE = g2.getEdgeDescriptor(currV, *adjItr);
				const int w = g2[currE].weight;

				pair<BoostGraph::edge_descriptor, bool> forE = add_edge(currV, *adjItr, g);
				pair<BoostGraph::edge_descriptor, bool> revE = add_edge(*adjItr, currV, g);
				g[forE.first].weight = w;
				g[revE.first].weight = w;
				g[*adjItr].visited = true;
				g[*adjItr].pred = currV;
				q.push(*adjItr);
			}
		}
		q.pop();
	}
	if(!this->pathToAllVisited())
		this->findSpanningForrest(g2);
}
//msfPrim
//Finds the minimum spanning forrest, sf, from some graph, g.
void Graph::msfPrim(Graph &g2)
{
	pair<BoostGraph::vertex_iterator, BoostGraph::vertex_iterator> vItrRange = vertices(g);
	pair<BoostGraph::vertex_iterator, BoostGraph::vertex_iterator> vItrRange2 = g2.getVertices();

	this->clearVisited();
	this->setNodeWeights(LARGE_VAL);
	g[*vItrRange.first].weight = 0;

	heapV<BoostGraph::vertex_descriptor, BoostGraph> pq;
	vector<BoostGraph::vertex_descriptor> vertexV;
	int size = 0;

	for(BoostGraph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; vItr++)
	{
		vertexV.push_back(*vItr);
		size++;
	}

	pq.initializeMinHeap(vertexV, g);
	BoostGraph::vertex_descriptor currVert;
	for(int i = 0; i < size; i++)
	{
		currVert = pq.extractMinHeapMinimum(g);
		g[currVert].visited = true;
		if(g[currVert].weight == LARGE_VAL)
			g[currVert].weight = 0;

		if(g[currVert].weight != 0)
		{
			pair<BoostGraph::edge_descriptor, bool> firstDir = add_edge(currVert, g[currVert].pred, g);
			g[firstDir.first].weight = g[currVert].weight;
			pair<BoostGraph::edge_descriptor, bool> secondDir = add_edge(g[currVert].pred, currVert, g);
			g[secondDir.first].weight = g[currVert].weight;
		}
		int WEIGHT = g[currVert].weight;

		pair<BoostGraph::adjacency_iterator, BoostGraph::adjacency_iterator> aItrRange = g2.getAdjVertices(currVert);
		for(BoostGraph::adjacency_iterator aItr = aItrRange.first; aItr != aItrRange.second; aItr++)
		{
			BoostGraph::vertex_descriptor w = *aItr;
			if(!g[w].visited)
			{				
				BoostGraph::edge_descriptor currE = g2.getEdgeDescriptor(currVert, w);
				if(g2[currE].weight < g[w].weight)
				{
					BoostGraph::vertex_descriptor N = *aItr;
					int W2 = g[w].weight;

					g[w].weight = g2[currE].weight;
					g[w].pred = currVert;
					int index = pq.getIndex(w);
					pq.minHeapDecreaseKey(index, g);
				}
			}
		}
	}
}
//* * * * * * * * * * * * * *
//* * * SEARCH FUNCTIONS * * *
//* * * * * * * * * * * * * * 
//BFS
//Performs a BFS starting with the first vertex in the stored graph. Sets all visited nodes to visited = true.
void Graph::BFS()
{
	this->clearVisited();
	pair<BoostGraph::vertex_iterator, BoostGraph::vertex_iterator> vItrRange = vertices(g);
	BoostGraph::vertex_iterator start = vItrRange.first;
	queue<BoostGraph::vertex_descriptor> q;
	q.push(*start);
	g[*start].visited = true;

	while(!q.empty())
	{
		BoostGraph::vertex_descriptor currV = q.front();
		pair<BoostGraph::adjacency_iterator, BoostGraph::adjacency_iterator> adjItrRange = this->getAdjVertices(currV);
		for(BoostGraph::adjacency_iterator adjItr = adjItrRange.first; adjItr != adjItrRange.second; adjItr++)
		{
			if(!g[*adjItr].visited)
			{
				g[*adjItr].visited = true;
				q.push(*adjItr);
			}
		}
		q.pop();
	}
}
//bellmanFord
//Finds shortest path to all nodes using the Bellman Ford algorithm, returns whether a shortest path has been established for all nodes.
bool Graph::bellmanFord(BoostGraph::vertex_descriptor s) 
{
	this->setNodeWeights(LARGE_VAL);
	this->clearVisited();
	g[s].weight = 0;
	const int numNodes = num_vertices(g);

	pair<BoostGraph::edge_iterator,BoostGraph::edge_iterator> eItrRange = edges(g);
	for(int i = 1; i < numNodes; i++)
	{
		for(BoostGraph::edge_iterator eItr = eItrRange.first; eItr != eItrRange.second; eItr++)
		{
			BoostGraph::vertex_descriptor sourceV = source(*eItr, g);
			BoostGraph::vertex_descriptor targetV = target(*eItr, g);
			g[targetV].visited = true;
			this->relax(sourceV, targetV, *eItr);
		}
	}
	for(BoostGraph::edge_iterator eItr = eItrRange.first; eItr != eItrRange.second; eItr++)
	{
		BoostGraph::vertex_descriptor sourceV = source(*eItr, g);
		BoostGraph::vertex_descriptor targetV = target(*eItr, g);
		if(g[targetV].weight > g[sourceV].weight + g[*eItr].weight)
			return false;
	}

	return this->pathToAllWeight();
}
//dijstra
//Uses Dijstra's very famous and super rad algorithm to find that shortest path. No negative nodes allowed, baby.
bool Graph::dijstra(BoostGraph::vertex_descriptor start)
{
	this->clearVisited();
	this->setNodeWeights(LARGE_VAL);
	g[start].weight = 0;

	heapV<BoostGraph::vertex_descriptor, BoostGraph> pq;
	vector<BoostGraph::vertex_descriptor> vertexV;

	pair<BoostGraph::vertex_iterator, BoostGraph::vertex_iterator> vItrRange = vertices(g);
	for(BoostGraph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; vItr++)
		vertexV.push_back(*vItr);


	pq.initializeMinHeap(vertexV, g);
	BoostGraph::vertex_descriptor currVert;
	while(!pq.empty())
	{
		currVert = pq.extractMinHeapMinimum(g);
		g[currVert].visited = true;

		pair<BoostGraph::adjacency_iterator, BoostGraph::adjacency_iterator> vItrRange = adjacent_vertices(currVert, g);
		for(BoostGraph::adjacency_iterator vItr = vItrRange.first; vItr != vItrRange.second; vItr++)
		{
			BoostGraph::vertex_descriptor w = *vItr;
			if(!g[w].visited)
			{
				pair<BoostGraph::edge_descriptor, bool> edgeU2V = edge(currVert, w, g);
				bool changeMade = this->relax(currVert, w, edgeU2V.first);
				if(changeMade)
				{
					int i = pq.getIndex(w);
					pq.minHeapDecreaseKey(i, g);
				}
			}
		}
	}	
	return this->pathToAllWeight();
}
//findPathDFSRecursive
//Finds path with recursive DFS
stack<BoostGraph::vertex_descriptor> Graph::findPathDFSRecursive(BoostGraph::vertex_descriptor start, BoostGraph::vertex_descriptor target, stack<BoostGraph::vertex_descriptor> &s)
{ 
	g[start].visited = true;

	if(start == target)
	{
		s.push(start);
		return s;
	}
	else
	{
		pair<BoostGraph::adjacency_iterator, BoostGraph::adjacency_iterator> vItrRange = adjacent_vertices(start, g);
		for(BoostGraph::adjacency_iterator vItr = vItrRange.first; vItr != vItrRange.second; vItr++)
		{
			if(g[*vItr].visited == false)
			{
				this->findPathDFSRecursive(*vItr, target, s);
				if(!s.empty())
				{
					s.push(*vItr);	
					break;
				}
			}
		}
		return s;
	}
}
//findPathDFSStack
//Finds path with depth first search
stack<BoostGraph::vertex_descriptor> Graph::findPathDFSStack(BoostGraph::vertex_descriptor start, BoostGraph::vertex_descriptor target)
{
	stack<BoostGraph::vertex_descriptor> s;
	s.push(start);
	g[start].visited = true;

	while(!s.empty())
	{
		bool unVisitedNeighbors = false;
		BoostGraph::vertex_descriptor vert = s.top();

		pair<BoostGraph::adjacency_iterator, BoostGraph::adjacency_iterator> vItrRange = adjacent_vertices(vert, g);
		for(BoostGraph::adjacency_iterator vItr = vItrRange.first; vItr != vItrRange.second; vItr++)
		{
			BoostGraph::vertex_descriptor w = *vItr;
			if(g[w].visited == false)
			{
				g[w].visited = true;
				unVisitedNeighbors = true;
				s.push(w);
				break;
			}
			if(w == target)
			{
				s.push(w);
				return s;
			}
		}
		if(!unVisitedNeighbors)
			s.pop();
	}
	return s;
}
//clearStack
//Deletes content of stack
void clearStack(stack<BoostGraph::vertex_descriptor> &s)
{
	while(!s.empty())
		s.pop();
}
//findPathDFSShortest
//finds shortest path recursively with DFS
stack<BoostGraph::vertex_descriptor> Graph::findPathDFSShortest(BoostGraph::vertex_descriptor start, BoostGraph::vertex_descriptor target, stack<BoostGraph::vertex_descriptor> &s)
{
	if(start == target)
	{
		s.push(start);
		return s;
	}
	g[start].visited = true;
	int shortestPath = 99999999;
	stack<BoostGraph::vertex_descriptor> bestPathFromStart;

	pair<BoostGraph::adjacency_iterator, BoostGraph::adjacency_iterator> vItrRange = adjacent_vertices(start, g);
	for(BoostGraph::adjacency_iterator vItr = vItrRange.first; vItr != vItrRange.second; vItr++)
	{
		if(!g[*vItr].visited)
		{
			this->findPathDFSShortest(*vItr, target, s);
			g[*vItr].visited = false;
			int currentSize = s.size();
			if( (currentSize >= 1) && (currentSize + 1 < shortestPath) && (*vItr != target) )
			{
				bestPathFromStart = s;
				bestPathFromStart.push(*vItr);
				shortestPath = currentSize++;
				clearStack(s);
			}	
		}
	}
	if(!bestPathFromStart.empty())
		s = bestPathFromStart;
	return s;
}
//createStack
//Help function for findPathBFS. Returns stack of shortest path.
stack<BoostGraph::vertex_descriptor> Graph::createStack(stack<BoostGraph::vertex_descriptor> &s, BoostGraph::vertex_descriptor start, BoostGraph::vertex_descriptor target)
{
	BoostGraph::vertex_descriptor previous = target;
	while(previous != start)
	{
		s.push(previous);
		previous = g[previous].pred;
	}
	s.push(start);
	return s;
}
//findPathBFS
//Finds shortest path with BFS
stack<BoostGraph::vertex_descriptor> Graph::findPathBFS(BoostGraph::vertex_descriptor start, BoostGraph::vertex_descriptor target)
{
	queue<BoostGraph::vertex_descriptor> q;
	stack<BoostGraph::vertex_descriptor> s;
	g[start].visited = true;

	q.push(start);

	while(!q.empty())
	{
		BoostGraph::vertex_descriptor front = q.front();
		pair<BoostGraph::adjacency_iterator, BoostGraph::adjacency_iterator> vItrRange = adjacent_vertices(front, g);
		for(BoostGraph::adjacency_iterator vItr = vItrRange.first; vItr != vItrRange.second; vItr++)
		{
			if(!g[*vItr].visited)
			{
				g[*vItr].pred = front;
				g[*vItr].visited = true;
				q.push(*vItr);
				if(*vItr == target)
					return this->createStack(s, start, target);
			}
		}
		q.pop();
	}
	return s;
}



