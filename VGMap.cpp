#include <iostream>
#include <cstdlib>
#include "VGMap.h"

using namespace std;


Graph* createGraph(int X, int Y) {
	Graph *graph = new Graph;
	graph->x = X;
	graph->y = Y;
	graph->arr = new AdjList*[X];
	for (int i = 0; i < X; i++) {
		graph->arr[i] = new AdjList[Y];
	}

	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			graph->arr[i][j].head = NULL;
		}
	}

	return graph;
}


Node *newNode(Coords *vals) {
	Node *ptr = new Node;
	ptr->data = vals;
	ptr->next = NULL;
	return ptr;
}

void addEdge(Graph *graph, Coords *src, Coords *dest) {
	//add node at beginning of arr
	Node *ptr = newNode(dest);
	ptr->next = graph->arr[src->x][src->y].head;
	graph->arr[src->x][src->y].head = ptr;
	//connect from dest to src
	ptr = newNode(src);
	ptr->next = graph->arr[dest->x][dest->y].head;
	graph->arr[dest->x][dest->y].head = ptr;
}

void printGraph(Graph* graph) {
	//loop over every adjacency list
	for (int i = 0; i < graph->x; i++) {
		for (int j = 0; j < graph->y; j++) {
			Node *root = graph->arr[i][j].head;
			cout << "Adjacency list of vertex " << i + 1 << "," << j + 1 << endl;
			//loop over each node in list
			while (root != NULL) {
				cout << root->data->x + 1 << "," << root->data->y + 1 << " -> ";
				root = root->next;
			}
			cout << endl;
		}
	}
}


