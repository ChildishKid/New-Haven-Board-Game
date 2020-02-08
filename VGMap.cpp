#include <iostream>
#include <cstdlib>
#include<map>
#include<vector>
#include "VGMap.h"

using namespace std;

VGMap::Circle::Circle(int x_value, int y_value) {
	x = new int(x_value);
	y = new int(y_value);
	colour = NULL;
	cost = new int(y_value + 1);
	status = NULL;
	adjacent = new vector<Circle*>();
}

VGMap::Circle::Circle() {
	x = 0;
	y = 0;
	colour = NULL;
	cost = 0;
	status = NULL;
	adjacent = new vector<Circle*>();
}

VGMap::Circle::~Circle() {
	delete x;
	delete y;
	delete colour;
	delete cost;
	delete status;
	delete adjacent;
	x = NULL;
	y = NULL;
	colour = NULL;
	cost = NULL;
	status = NULL;
	adjacent = NULL;
}

void VGMap::Circle::setX(int x_value) {
	*x = x_value;
}

void VGMap::Circle::setY(int y_value) {
	*y = y_value;
}

void VGMap::Circle::setColour(Type clr) {
	*colour = clr;
}

void VGMap::Circle::setCost(int val) {
	*cost = val;
}

void VGMap::Circle::setStatus(string stat) {
	*status = stat;
}

void VGMap::Circle::addAdj(Circle* obj) {
	adjacent->push_back(obj);
}


int VGMap::Circle::getX() const {
	return *x;
}

int VGMap::Circle::getY() const {
	return *y;
}

Type VGMap::Circle::getColour() const {
	return *colour;
}

int VGMap::Circle::getCost() const{
	return *cost;
}

string VGMap::Circle::getStatus() const {
	return *status;
}

vector<VGMap::Circle*> VGMap::Circle::getAdj() const {
	return *adjacent;
}

VGMap::VGMap(string player) {
	playerName = player;
	playerBoard = new map<pair<int, int>, Circle*>();

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			(*playerBoard)[{i, j}] = new VGMap::Circle(i, j);
		}
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {

			if (!(i - 1 < 0)) {
				(*playerBoard)[{i, j}]->addAdj((*playerBoard)[{(i - 1), j}]);
			}

			if (!(i + 1 > 4)) {
				(*playerBoard)[{i, j}]->addAdj((*playerBoard)[{(i + 1), j}]);
			}

			if (!(j - 1 < 0)) {
				(*playerBoard)[{i, j}]->addAdj((*playerBoard)[{i, (j - 1)}]);
			}

			if (!(j + 1 > 5)) {
				(*playerBoard)[{i, j}]->addAdj((*playerBoard)[{i, (j + 1)}]);
			}

		}
	}


}

VGMap::VGMap() {
	playerName = "";
	playerBoard = new map<pair<int, int>, Circle*>();
}

VGMap::~VGMap() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			delete (*playerBoard)[{i, j}];
			(*playerBoard)[{i, j}] = NULL;
		}
	}

	delete playerBoard;
	playerBoard = NULL;
}

VGMap::Circle* VGMap::getCircle(int x_value, int y_value) const {
	return (*playerBoard).at({ x_value, y_value });
}