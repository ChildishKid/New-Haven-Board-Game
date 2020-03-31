#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
using namespace std;
#include "GBMaps.h"
#include "Resources.h"

/* === Node === */
GBMaps::Node::Node(Type* t) {
	type = t;
};

GBMaps::Node::Node() {
	type = new Type(Type::None);
}

Type GBMaps::Node::getType() {
	return *type;
};

void GBMaps::Node::setType(Type* t) {
	*type = *t;
};

bool operator==(const GBMaps::Node& lhs, const GBMaps::Node& rhs) {
    return &lhs==&rhs;
};

bool operator!=(const GBMaps::Node &lhs, const GBMaps::Node &rhs) {
    return !(lhs == rhs);
};

/* === Square === */
GBMaps::Square::Square(int x_value, int y_value) {
	x = new int(x_value);
	y = new int(y_value);
	topLeft = new Node(new Type{Type::None});
	topRight = new Node(new Type{Type::None});
	bottomLeft = new Node(new Type{Type::None});
	bottomRight = new Node(new Type{Type::None});
	status = new bool(false);
	size = new int(0);
	adjacent = new vector<Square*>();
}

GBMaps::Square::Square() {
	x = new int(0);
	y = new int(0);
	topLeft = new Node(new Type{ Type::None });
	topRight = new Node(new Type{ Type::None });
	bottomLeft = new Node(new Type{ Type::None });
	bottomRight = new Node(new Type{ Type::None });
	status = new bool(false);
	size = new int(0);
	adjacent = new vector<Square*>();
}

GBMaps::Square::~Square() {
	delete topLeft;
	delete topRight;
	delete bottomLeft;
	delete bottomRight;
	delete x;
	delete y;
	delete status;
	delete adjacent;
	delete size;
	topLeft = NULL;
	topRight = NULL;
	bottomLeft = NULL;
	bottomRight = NULL;
	x = NULL;
	y = NULL;
	status = NULL;
	adjacent = NULL;
	size = NULL;
}

void GBMaps::Square::setTopLeft(Node tL) {
	*topLeft = tL;
}

void GBMaps::Square::setTopRight(Node tR) {
	*topRight = tR;
}

void GBMaps::Square::setBottomLeft(Node bL) {
	*bottomLeft = bL;
}

void GBMaps::Square::setBottomRight(Node bR) {
	*bottomRight = bR;
}

void GBMaps::Square::setX(int x_value) {
	*x = x_value;
}

void GBMaps::Square::setY(int y_value) {
	*y = y_value;
}

void GBMaps::Square::setStatus(bool value) {
	*status = value;
}

void GBMaps::Square::addAdj(Square* obj) {
	adjacent->push_back(obj);
	(*size)++;
}

GBMaps::Node* GBMaps::Square::getTopLeft() {
	return topLeft;
}

GBMaps::Node* GBMaps::Square::getTopRight() {
	return topRight;
}

GBMaps::Node* GBMaps::Square::getBottomLeft() {
	return bottomLeft;
}

GBMaps::Node* GBMaps::Square::getBottomRight() {
	return bottomRight;
}

vector<GBMaps::Square*> GBMaps::Square::getAdj() const {
	return *adjacent;
}

int GBMaps::Square::getX() const {
	return *x;
}

int GBMaps::Square::getY() const {
	return *y;
}

int GBMaps::Square::getSize() const {
	return *size;
}

bool GBMaps::Square::getStatus() const {
	return *status;
}

/* === GBMaps === */
GBMaps::GBMaps(int numOfPlayers) {
	numberOfPlayers = new int(numOfPlayers);
	gameBoard = new map<pair<int, int>, Square*>();	
	setUpBoard();
	setUpAdjacencies();

	if (*numberOfPlayers == 2)
		placeInitialResources(0, 0);
	else if (*numberOfPlayers == 3) 
		placeInitialResources(0, 1);
	else 
		placeInitialResources(1, 1);

	iterate = gameBoard->begin();
}

GBMaps::GBMaps() {
	// Default constructor sets it to two players
	numberOfPlayers = new int(2);
	gameBoard = new map<pair<int, int>, Square*>();
	setUpBoard();
	setUpAdjacencies();
	placeInitialResources(0, 0);
	iterate = gameBoard->begin();
}

GBMaps::~GBMaps() {
	iterate = gameBoard->begin();
	for (; iterate != end(); ++iterate) {
		delete(iterate->second);
		iterate->second = NULL;
	}

	delete gameBoard;
	delete height;
	delete width;
	delete numberOfPlayers;

	gameBoard = NULL;
	height = NULL;
	width = NULL;
	numberOfPlayers = NULL;
}

void GBMaps::setUpBoard() {

	if (getNumberOfPlayers() == 2 || getNumberOfPlayers() == 3) {
		width = new int(5);
		height = (getNumberOfPlayers() == 2) ? new int(5) : new int(7);

		// Set up each square piece
		for (int i = 0; i < *width; i++) {
			for (int j = 0; j < *height; j++) {
				(*gameBoard)[{i, j}] = new GBMaps::Square(i, j);
			}
		}
	}

	if (getNumberOfPlayers() == 4) {
		width = new int(7);
		height = new int(7);

		// Set up each square piece
		for (int i = 0; i < *height; i++) {
			for (int j = 0; j < *width; j++) {
				if ((i == 0 && j == 0)
					|| (i == 0 && j == *width - 1)
					|| (i == *height - 1 && j == 0)
					|| (i == *height - 1 && j == *width - 1)) {
					continue;
				}
				(*gameBoard)[{i, j}] = new Square(i, j);
			}
		}
	}
}

void GBMaps::setUpAdjacencies() {
	if (getNumberOfPlayers() == 2 || getNumberOfPlayers() == 3) {

		for (int i = 0; i < *width; i++) {
			for (int j = 0; j < *height; j++) {

				if (!(i - 1 < 0)) {
					(*gameBoard)[{i, j}]->addAdj((*gameBoard)[{(i - 1), j}]);
				}

				if (!(i + 1 > 4)) {
					(*gameBoard)[{i, j}]->addAdj((*gameBoard)[{(i + 1), j}]);
				}

				if (!(j - 1 < 0)) {
					(*gameBoard)[{i, j}]->addAdj((*gameBoard)[{i, (j - 1)}]);
				}

				if (!(j + 1 > 4)) {
					(*gameBoard)[{i, j}]->addAdj((*gameBoard)[{i, (j + 1)}]);
				}
			}
		}
	}

	if (getNumberOfPlayers() == 4) {

		for (int i = 0; i < *height; i++) {
			for (int j = 0; j < *width; j++) {

				if ((i == 0 && j == 0)
					|| (i == 0 && j == *width - 1)
					|| (i == *height - 1 && j == 0)
					|| (i == *height - 1 && j == *width - 1)) {
					continue;
				}

				if (!(i - 1 < 0)
					&& !(i - 1 == 0 && j == 0)
					&& !(i - 1 == 0 && j == *width - 1)) {
					(*gameBoard)[{i, j}]->addAdj((*gameBoard)[{(i - 1), j}]);
				}

				if (!(i + 1 == *height)
					&& !(i + 1 == *height - 1 && j == 0)
					&& !(i + 1 == *height - 1 && j == *width - 1)) {
					(*gameBoard)[{i, j}]->addAdj((*gameBoard)[{(i + 1), j}]);
				}

				if (!(j - 1 < 0)
					&& !(i == 0 && j - 1 == 0)
					&& !(i == *height - 1 && j - 1 == 0)) {
					(*gameBoard)[{i, j}]->addAdj((*gameBoard)[{i, (j - 1)}]);
				}

				if (!(j + 1 == *width)
					&& !(i == 0 && j + 1 == *width - 1)
					&& !(i == *height - 1 && j + 1 == *width - 1)) {
					(*gameBoard)[{i, j}]->addAdj((*gameBoard)[{i, (j + 1)}]);
				}
			}
		}
	}
}

GBMaps::Square* GBMaps::getSquare(int x_value, int y_value) {
	return (*gameBoard).at({ x_value, y_value });
}

map<pair<int, int>, GBMaps::Square*>::iterator GBMaps::begin() {
	return (*gameBoard).begin();
}

map<pair<int, int>, GBMaps::Square*>::iterator GBMaps::end() {
	return (*gameBoard).end();
}

int GBMaps::getHeight() {
	return *height;
}

int GBMaps::getWidth() {
	return *width;
}

int GBMaps::getNumberOfPlayers() {
	return *numberOfPlayers;
}

bool GBMaps::squareAboveExists(int x_value, int y_value) {
	return (y_value != getHeight() - 1 || (getNumberOfPlayers() == 4 &&
		y_value != getHeight() - 2 && (x_value != 0 || x_value != getWidth() - 1)));
};

bool GBMaps::squareBelowExists(int x_value, int y_value) {
	return (y_value != 0 || (getNumberOfPlayers() == 4 &&
		y_value != 1 && (x_value != 0 || x_value != getWidth() - 1)));
};

bool GBMaps::squareToLeftExists(int x_value, int y_value) {
	return (x_value != 0 || (getNumberOfPlayers() == 4 &&
		x_value != 1 && (y_value != 0 || y_value != getHeight() - 1)));
};

bool GBMaps::squareToRightExists(int x_value, int y_value) {
	return (x_value != getWidth() - 1 || (getNumberOfPlayers() == 4 &&
		x_value != getWidth() - 2 && (y_value != 0 || y_value != getHeight() - 1)));
};

void GBMaps::setHeight(int h) {
	*height = h;
}

void GBMaps::setWidth(int w) {
	*width = w;
}

void GBMaps::setNumberOfPlayers(int players) {
	*numberOfPlayers = players;
}

int GBMaps::getNumberOfEmptySlots() {
	
	int emptySlots = 0;
	iterate = begin();
	while (iterate != end()) {
		if (iterate->second->getStatus() == 0) {
			emptySlots++;
		}
		iterate++;
	}

	return emptySlots;
}

void GBMaps::placeInitialResources(int x_value, int y_value) {

	(*gameBoard)[{x_value, y_value}]->setStatus(true);
	(*gameBoard)[{x_value, y_value}]->setTopLeft(new Type(Type::Stone));
	(*gameBoard)[{x_value, y_value}]->setTopRight(new Type(Type::Sheep));
	(*gameBoard)[{x_value, y_value}]->setBottomLeft(new Type(Type::Timber));
	(*gameBoard)[{x_value, y_value}]->setBottomRight(new Type(Type::Timber));

	(*gameBoard)[{x_value + 4, y_value}]->setStatus(true);
	(*gameBoard)[{x_value + 4, y_value}]->setTopLeft(new Type(Type::Wheat));
	(*gameBoard)[{x_value + 4, y_value}]->setTopRight(new Type(Type::Sheep));
	(*gameBoard)[{x_value + 4, y_value}]->setBottomLeft(new Type(Type::Wheat));
	(*gameBoard)[{x_value + 4, y_value}]->setBottomRight(new Type(Type::Timber));

	(*gameBoard)[{x_value, y_value + 4}]->setStatus(true);
	(*gameBoard)[{x_value, y_value + 4}]->setTopLeft(new Type(Type::Sheep));
	(*gameBoard)[{x_value, y_value + 4}]->setTopRight(new Type(Type::Stone));
	(*gameBoard)[{x_value, y_value + 4}]->setBottomLeft(new Type(Type::Sheep));
	(*gameBoard)[{x_value, y_value + 4}]->setBottomRight(new Type(Type::Wheat));

	(*gameBoard)[{x_value + 4, y_value + 4}]->setStatus(true);
	(*gameBoard)[{x_value + 4, y_value + 4}]->setTopLeft(new Type(Type::Stone));
	(*gameBoard)[{x_value + 4, y_value + 4}]->setTopRight(new Type(Type::Stone));
	(*gameBoard)[{x_value + 4, y_value + 4}]->setBottomLeft(new Type(Type::Timber));
	(*gameBoard)[{x_value + 4, y_value + 4}]->setBottomRight(new Type(Type::Wheat));
}