#include <iostream>
#include <cstdlib>
#include<map>
#include<vector>
#include "VGMap.h"
using namespace std;

VGMap::Circle::Circle(int x_value, int y_value) {
	x = new int(x_value);
	y = new int(y_value);
	cost = new int(y_value + 1);
	status = new bool(false);
	adjacent = new vector<Circle*>();
	building = NULL;
}

VGMap::Circle::Circle() {
	x = new int(0);
	y = new int(0);
	cost = new int(0);
	status = new bool(false);
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

void VGMap::Circle::setStatus(bool stat) {
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

int VGMap::Circle::getCost() const{
	return *cost;
}

bool VGMap::Circle::getStatus() const {
	return *status;
}

vector<VGMap::Circle*> VGMap::Circle::getAdj() const {
	return *adjacent;
}

Building* VGMap::Circle::getBuilding() const {
	return building;
}

bool VGMap::Circle::validateCircle(Type build) {
	vector<Circle*> adj = this->getAdj();
	for (int i = 0; i < adj.size(); ++i) {
		if (*(adj.at(i)->getBuilding()->getType()) == build) {
			return true;
		}
	}
	return false;
}

VGMap::VGMap(string name, int id) {
	playerName = new string(name);
	playerID = new int(id);
	playerBoard = new map<pair<int, int>, Circle*>();
	width = new int (5);
	height = new int (6);
	setupBoard();
	iterate = playerBoard->begin();
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
	iterate = playerBoard->begin();
}

VGMap::~VGMap() {
	/*
	for (int i = 0; i < *width; i++) {
		for (int j = 0; j < *height; j++) {
			delete (*playerBoard)[{i, j}];
			(*playerBoard)[{i, j}] = NULL;
		}
	}
	*/

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
}
 
int VGMap::getPlayerID() {
	return *playerID;
}

int VGMap::getNumberOfEmptySlots() {

	int emptySlots = 0;
	iterate = begin();
	while (iterate != end()) {
		if (iterate->second->getBuilding() == NULL) {
			emptySlots++;
		}
		iterate++;
	}

	return emptySlots;
}

map<pair<int, int>, VGMap::Circle*>::iterator VGMap::begin() {
	return (*playerBoard).begin();
}

map<pair<int, int>, VGMap::Circle*>::iterator VGMap::end() {
	return (*playerBoard).end();
}

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

bool VGMap::validateTypeAdjacency(int x, int y, Type type) {
	map<pair<int, int>, Circle*>::iterator it = begin();

	while (it != end()) {
		if (it->second->getBuilding() == NULL) {
			it++;
			continue;
		}

		if (*(it->second->getBuilding()->getType()) == type)
			goto past;
		it++;
	}
	return true;

past:
	vector<Circle*> adj = getCircle(x, y)->getAdj();
	for (int i = 0; i < adj.size(); i++) {
		if (adj.at(i)->getBuilding() == NULL)
			continue;

		if (*(adj.at(i)->getBuilding()->getType()) == type)
			return true;
	}
	return false;

}