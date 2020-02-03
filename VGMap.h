#pragma once

#include<iostream>
#include<cstdlib>

using namespace std;

struct Coords {
	int x;
	int y;
};

struct Node{
	Coords *data;
	Node *next;
};

struct AdjList{
	Node *head;
};

struct Graph{
	int x;
	int y;
	AdjList **arr;
};



Node *newNode(int);
Graph *createGraph(int, int);
void addEdge(Graph*, Coords*, Coords*);
void printGraph(Graph*);

