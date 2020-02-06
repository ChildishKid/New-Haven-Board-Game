#include <string>
#include <iostream>
using namespace std;
#include "GBMaps.h"

GBMaps::Node::Node(Type* t) {
	type = t;
};

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

GBMaps::Square::~Square() {
	delete x;
	delete y;
	delete topLeft;
	delete topRight;
	delete bottomLeft;
	delete bottomRight;
	x = NULL;
	y = NULL;
	topLeft = NULL;
	topRight = NULL;
	bottomLeft = NULL;
	bottomRight = NULL;
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

		// Set up adjencies
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
		int max_width = 7;
		int max_height = 7;

		// Set up each square piece
		for (int i = 0; i < max_height; i++) {
			for (int j = 0; j < max_width; j++) {
				if ((i == 0 && j == 0)
					|| (i == 0 && j == max_width - 1)
					|| (i == max_height - 1 && j == 0)
					|| (i == max_height - 1 && j == max_width - 1)) {
					continue;
				}
				(*gameBoard)[{i, j}] = new Square(i, j);
			}
		}

		// Set up adjencies
		for (int i = 0; i < max_height; i++) {
			for (int j = 0; j < max_width; j++) {

				if ((i == 0 && j == 0)
					|| (i == 0 && j == max_width - 1)
					|| (i == max_height - 1 && j == 0)
					|| (i == max_height - 1 && j == max_width - 1)) {
					continue;
				}

				if (!(i - 1 < 0)
					&& !(i - 1 == 0 && j == 0)
					&& !(i - 1 == 0 && j == max_width - 1)) {
					(*gameBoard)[{i, j}]->addAdj((*gameBoard)[{(i - 1), j}]);
				}

				if (!(i + 1 == max_height)
					&& !(i + 1 == max_height - 1 && j == 0)
					&& !(i + 1 == max_height - 1 && j == max_width - 1)) {
					(*gameBoard)[{i, j}]->addAdj((*gameBoard)[{(i + 1), j}]);
				}

				if (!(j - 1 < 0)
					&& !(i == 0 && j - 1 == 0)
					&& !(i == max_height - 1 && j - 1 == 0)) {
					(*gameBoard)[{i, j}]->addAdj((*gameBoard)[{i, (j - 1)}]);
				}

				if (!(j + 1 == max_width)
					&& !(i == 0 && j + 1 == max_width - 1)
					&& !(i == max_height - 1 && j + 1 == max_width - 1)) {
					(*gameBoard)[{i, j}]->addAdj((*gameBoard)[{i, (j + 1)}]);
				}
			}
		}
	}
}

GBMaps::GBMaps(int numOfPlayers) {
	numberOfPlayers = new int(numOfPlayers);
	gameBoard = new map<pair<int, int>, Square*>();	
	setUpBoard();
	iterate = gameBoard->begin();
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
		y_value != getHeight() - 2 && (x_value !=0 || x_value != getWidth() - 1)));
};

bool GBMaps::squareBelowExists(int x_value, int y_value) {
	return (y_value != 0 || (getNumberOfPlayers() == 4 && 
		y_value != 1 && (x_value !=0 || x_value != getWidth() - 1)));
};

bool GBMaps::squareToLeftExists(int x_value, int y_value) {
	return (x_value != 0 || (getNumberOfPlayers() == 4 && 
		x_value != 1 && (y_value !=0 || y_value != getHeight() - 1)));
};

bool GBMaps::squareToRightExists(int x_value, int y_value) {
	return (x_value != getWidth() - 1 || (getNumberOfPlayers() == 4 && 
		x_value != getWidth() - 2 && (y_value !=0 || y_value != getHeight() - 1)));
};
