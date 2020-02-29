#include <iostream>
#include <cstdlib>
#include<map>
#include<vector>
#include "VGMap.h"

using namespace std;

VGMap::Circle::Circle(int x_value, int y_value) {
	x = new int(x_value);
	y = new int(y_value);
	type = new Type(Type::None);
	cost = new int(y_value + 1);
	status = new string("Empty");
	adjacent = new vector<Circle*>();
	building = NULL;
}

VGMap::Circle::Circle() {
	x = 0;
	y = 0;
	type = new Type(Type::None);
	cost = 0;
	status = new string("Empty");
	adjacent = new vector<Circle*>();
	building = NULL;
}

VGMap::Circle::~Circle() {
	delete x;
	delete y;
	delete cost;
	delete status;
	delete adjacent;
	x = NULL;
	y = NULL;
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

void VGMap::Circle::setCost(int val) {
	*cost = val;
}

void VGMap::Circle::setStatus(string stat) {
	*status = stat;
}

void VGMap::Circle::setBuilding(Building* b) {
	building = b;
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

Type VGMap::Circle::getType() const {
	return *type;
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

Building* VGMap::Circle::getBuilding() const {
	return building;
}

VGMap::VGMap(string player) {
	playerName = new string(player);
	playerBoard = new map<pair<int, int>, Circle*>();
	width = new int (5);
	height = new int (6);
	setupBoard();
}

VGMap::VGMap() {
	playerName = new string("");
	playerBoard = new map<pair<int, int>, Circle*>();
	width = new int(5);
	height = new int (6);

	for (int i = 0; i < *width; i++) {
		for (int j = 0; j < *height; j++) {
			(*playerBoard)[{i, j}] = new VGMap::Circle(i, j);
		}
	}

	for (int i = 0; i < *width; i++) {
		for (int j = 0; j < *height; j++) {

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
	setupBoard();
}

VGMap::~VGMap() {
	for (int i = 0; i < *width; i++) {
		for (int j = 0; j < *height; j++) {
			delete (*playerBoard)[{i, j}];
			(*playerBoard)[{i, j}] = NULL;
		}
	}

	delete playerBoard;
	delete width;
	delete height;
	delete playerName;
	playerBoard = NULL;
	playerName = NULL;
	width = NULL;
	height = NULL;
}

VGMap::Circle* VGMap::getCircle(int x_value, int y_value) const {
	return (*playerBoard).at({ x_value, y_value });
}

int VGMap::getWidth() {
	return *width;
}

int VGMap::getHeight() {
	return *height;
}

string VGMap::getPlayerName() {
	return *playerName;
  
void VGMap::setupBoard() {
	
	for (int i = 0; i < *width; i++) {
		for (int j = 0; j < *height; j++) {
			(*playerBoard)[{i, j}] = new VGMap::Circle(i, j);
		}
	}

	for (int i = 0; i < *width; i++) {
		for (int j = 0; j < *height; j++) {

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