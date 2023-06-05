//
//  graph.cpp
//  Project4
//
//  Created by Bein, Doina on 4/21/18.
//  Copyright © 2018 Bein, Doina. All rights reserved.
//

#include "graph.h"
#include <iostream>
#include <fstream>
#include <list>
#include <stack>
#include <vector>

// default constructor
Graph::Graph()
{
	// Set the variables to default values
	nNode = 0;
	nEdge = 0;
	nodeValue = nullptr;
	adj = nullptr;
	budget = 0.0f;
}

// constructor with two arguments representing the number of nodes, initial budget
Graph::Graph(int rno, float rbudget)
{
	nNode = rno;
	budget = rbudget;
	nodeValue = new float[nNode];

	for (int i = 0; i < nNode; i++)
	{
		nodeValue[i] = 0.0f;
	}

	adj = new list<int>[rno];
}

// destructor to erase allocated memory
Graph::~Graph()
{
	// Delete the adjacency list and the node value array
	for (int i = 0; i < nNode; i++)
	{
		adj[i].clear();
	}
	delete[] adj;
	delete[] nodeValue;
}

// adds an edge between two nodes in the graph node1 and node2
void Graph::addEdge(int node1, int node2)
{
	nEdge++;
	adj[node1].push_back(node2);	// Add node2 to node1's list.
	adj[node2].push_back(node1);	// Add node1 to node2's list.
}

// sets a value for a node
void Graph::setValue(int node, float rval)
{
	nodeValue[node] = rval;
}

// sets the initial budget
void Graph::setBudget(float rbu)
{
	budget = rbu;
}

// return number of nodes
int Graph::getNSize()
{
	return nNode;
}

// return number of edges
int Graph::getESize()
{
	return nEdge;
}

// return current budget
float Graph::getBudget()
{
	return budget;
}

// returns the value of the node
float Graph::getValue(int node)
{
	return nodeValue[node];
}

// reads data from a specified file
void Graph::readData(string fileName)
{
	// Check if the text file exists.
	ifstream myfile(fileName);

	if (myfile.is_open())
	{
		while (!myfile.eof())	// While it is not at the end of file
		{
			float temp;

			myfile >> nNode;

			myfile >> temp;
			setBudget(temp);

			nodeValue = new float[nNode];	// Allocate new memory for nodeValue
			adj = new list<int>[nNode];		// Allocate new memory for adj list

			for (int i = 0; i < nNode; ++i)
			{
				myfile >> temp;
				setValue(i, temp);
			}
			while (!myfile.eof())
			{
				int node1, node2;	// Needed for reading the endpoints for each edge
				myfile >> node1 >> node2;
				if ((node1 >= 0) && (node2 >= 0) && (myfile.peek() == '\n'))
				{
					addEdge(node1, node2);
				}
			}
		}
		myfile.close();
	}
	else
	{
		cout << "Unable to open file.\n";
	}
}

//return the number of nodes visited using DFS starting at startNode and accumulating values at each node, as long as the budget remains positive
int Graph::DFS(int startNode)
{
	// First, check whether the budget is positive or not.
	// If it is, then traverse through the graph and accumulate the values
	// for each visited node.
	// This DFS will be performed with recursion from DFSHelper.

	// Create an array of nodes and label the vertices as not visited
	bool *visited = new bool[nNode];
	for (int i = 0; i < nNode; i++)
	{
		visited[i] = false;
	}

	float rbu = budget;
	int nNodeVisited = 0;
	// Call the DFSHelper function
	DFSHelper(rbu, nNodeVisited, startNode, visited);

	// Delete the allocated boolean, then return the number of nodes.
	delete visited;
	return nNodeVisited;
}

// Helper function for the DFS(int startNode)
void Graph::DFSHelper(float &rbu, int &nNodeVisited, int node, bool visited[])
{
	// Mark the current node as visited
	visited[node] = true;

	// Update the budget and check if it is still positive
	rbu = rbu + nodeValue[node];
	nNodeVisited++;

	//cout << "nNodesVisited =  " << nNodeVisited << "  Node = " << node << "  rbu = " << rbu << endl;
	if (rbu <= 0.0)
	{
		return;
	}

	// Use the iterator to inspect each edge
	list<int>::iterator i;
	for (i = adj[node].begin(); i != adj[node].end(); ++i)
	{
		if (!visited[*i])
		{
			DFSHelper(rbu, nNodeVisited, *i, visited);	// Save the current value
			if (rbu <= 0.0)
				break;
		}
	}
	return;
}

// return the starting node that gives a longest DFS run before running out of budget
// if there are multiple nodes with the same DFS run length, return the smallest node
int Graph::bestStartVertex()
{
	int bestNode = 0;
	int maxValue = DFS(bestNode);

	for (int node = 1; node < nNode; node++)
	{
		int temp = DFS(node);	// Call DFS to find the number of nodes starting from node
		if (temp > maxValue)
		{
			maxValue = temp;
			bestNode = node;
		}
	}
	return bestNode;
}