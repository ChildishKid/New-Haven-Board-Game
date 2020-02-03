#include <iostream>
#include <cstdlib>
#include "VGMap.h"


using namespace std;

int main() {

	Graph *graph;
	graph = createGraph(5, 6);

	Coords *c11 = new Coords{ 0,0 };
	Coords *c12 = new Coords{ 0,1 };
	Coords *c13 = new Coords{ 0,2 };
	Coords *c14 = new Coords{ 0,3 };
	Coords *c15 = new Coords{ 0,4 };
	Coords *c16 = new Coords{ 0,5 };
	Coords *c21 = new Coords{ 1,0 };
	Coords *c22 = new Coords{ 1,1 };
	Coords *c23 = new Coords{ 1,2 };
	Coords *c24 = new Coords{ 1,3 };
	Coords *c25 = new Coords{ 1,4 };
	Coords *c26 = new Coords{ 1,5 };
	Coords *c31 = new Coords{ 2,0 };
	Coords *c32 = new Coords{ 2,1 };
	Coords *c33 = new Coords{ 2,2 };
	Coords *c34 = new Coords{ 2,3 };
	Coords *c35 = new Coords{ 2,4 };
	Coords *c36 = new Coords{ 2,5 };
	Coords *c41 = new Coords{ 3,0 };
	Coords *c42 = new Coords{ 3,1 };
	Coords *c43 = new Coords{ 3,2 };
	Coords *c44 = new Coords{ 3,3 };
	Coords *c45 = new Coords{ 3,4 };
	Coords *c46 = new Coords{ 3,5 };
	Coords *c51 = new Coords{ 4,0 };
	Coords *c52 = new Coords{ 4,1 };
	Coords *c53 = new Coords{ 4,2 };
	Coords *c54 = new Coords{ 4,3 };
	Coords *c55 = new Coords{ 4,4 };
	Coords *c56 = new Coords{ 4,5 };

	addEdge(graph, c11, c12);
	addEdge(graph, c11, c21);
	addEdge(graph, c12, c13);
	addEdge(graph, c12, c22);
	addEdge(graph, c13, c14);
	addEdge(graph, c13, c23);
	addEdge(graph, c14, c15);
	addEdge(graph, c14, c24);
	addEdge(graph, c15, c16);
	addEdge(graph, c15, c25);
	addEdge(graph, c16, c26);
	addEdge(graph, c21, c22);
	addEdge(graph, c21, c31);
	addEdge(graph, c22, c23);
	addEdge(graph, c22, c32);
	addEdge(graph, c23, c24);
	addEdge(graph, c23, c33);
	addEdge(graph, c24, c25);
	addEdge(graph, c24, c34);
	addEdge(graph, c25, c26);
	addEdge(graph, c25, c35);
	addEdge(graph, c26, c36);
	addEdge(graph, c31, c32);
	addEdge(graph, c31, c41);
	addEdge(graph, c32, c33);
	addEdge(graph, c32, c42);
	addEdge(graph, c33, c34);
	addEdge(graph, c33, c43);
	addEdge(graph, c34, c35);
	addEdge(graph, c34, c44);
	addEdge(graph, c35, c36);
	addEdge(graph, c35, c45);
	addEdge(graph, c36, c46);
	addEdge(graph, c41, c42);
	addEdge(graph, c41, c51);
	addEdge(graph, c42, c43);
	addEdge(graph, c42, c52);
	addEdge(graph, c43, c44);
	addEdge(graph, c43, c53);
	addEdge(graph, c44, c45);
	addEdge(graph, c44, c54);
	addEdge(graph, c45, c46);
	addEdge(graph, c45, c55);
	addEdge(graph, c46, c56);
	addEdge(graph, c51, c52);
	addEdge(graph, c52, c53);
	addEdge(graph, c53, c54);
	addEdge(graph, c54, c55);
	addEdge(graph, c55, c56);

	printGraph(graph);


	return 0;

}