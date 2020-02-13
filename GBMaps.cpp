#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <afx.h>
using namespace std;
#include "GBMaps.h"
#include "Resources.h"

IMPLEMENT_SERIAL(GBMaps, CObject, 1)

GBMaps::Node::Node(Type* t) {
	type = t;
};

Type GBMaps::Node::getType() {
	return *type;
};

void GBMaps::Node::setType(Type* t) {
	*type = *t;
};

string GBMaps::Node::getTypeString() {
	if (Type::Wheat == *type) {
		return "Wheat";
	}
	else if (Type::Sheep == *type) {
		return "Sheep";
	}
	else if (Type::Timber == *type) {
		return "Timber";
	}
	else if (Type::Stone == *type) {
		return "Stone";
	}
	else if (Type::None == *type) {
		return "None";
	}
}

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

bool GBMaps::Square::getStatus() const {
	return *status;
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

		int max_width = 7;
		int max_height = 7;

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
	setUpAdjacencies();
	iterate = gameBoard->begin();
}

GBMaps::GBMaps() {

	// Default constructor sets it to two players
	numberOfPlayers = new int(2);
	gameBoard = new map<pair<int, int>, Square*>();
	setUpBoard();
	setUpAdjacencies();
	iterate = gameBoard->begin();
}

GBMaps::~GBMaps() {
	delete gameBoard;
	delete height;
	delete width;
	delete numberOfPlayers;

	gameBoard = NULL;
	height = NULL;
	width = NULL;
	numberOfPlayers = NULL;
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

void GBMaps::Serialize(CArchive& ar) {

	if (ar.IsStoring()) {

		ar << *numberOfPlayers;
		ar << *height;
		ar << *width;
		
		iterate = begin();

		for (; iterate != gameBoard->end(); ++iterate) {
			ar << iterate->second->getX();
			ar << iterate->second->getY();
			ar << iterate->second->getStatus();
			ar.WriteString(iterate->second->getTopLeft()->getTypeString().c_str());
			ar.WriteString(_T("\n"));
			ar.WriteString(iterate->second->getTopRight()->getTypeString());
			ar.WriteString(_T("\n"));
			ar.WriteString(iterate->second->getBottomLeft()->getTypeString());
			ar.WriteString(_T("\n"));
			ar.WriteString(iterate->second->getBottomRight()->getTypeString());
			ar.WriteString(_T("\n"));
		}
	}
	else {
		int input;

		ar >> input;
		numberOfPlayers = new int(input);
		ar >> input;
		height = new int(input);
		ar >> input;
		width = new int(input);

		int elements;
		if (*numberOfPlayers == 2) {
			elements = 25;
		}
		else if (*numberOfPlayers == 3) {
			elements = 35;
		}
		else {
			elements = 45;
		}

		cout << "Number of players: " << *numberOfPlayers << endl;
		cout << "Height: " << *height << endl;
		cout << "Width: " << *width << endl;

		gameBoard = new map<pair<int, int>, Square*>();

		for (int i = 0; i < elements; i++) {
			int x;
			ar >> x;
			int y;
			ar >> y;
			Square* square = new Square(x, y);

			bool status;
			ar >> status;
			square->setStatus(status);

			CString resourceTL;
			ar.ReadString(resourceTL);
			CString resourceTR;
			ar.ReadString(resourceTR);
			CString resourceBL;
			ar.ReadString(resourceBL);
			CString resourceBR;
			ar.ReadString(resourceBR);
			
			cout << square->getX() << " " << square->getY() << endl;
			cout << "Status: " << status << endl;
			cout << resourceTL << " " << resourceTR << " " << resourceBL << " " << resourceBR << " " << endl;

			if (resourceTL == "Wheat") {
				square->setTopLeft(Node(new Type(Type::Wheat)));
			}
			else if (resourceTL == "Sheep") {
				square->setTopLeft(Node(new Type(Type::Wheat)));
			}
			else if (resourceTL == "Timber") {
				square->setTopLeft(Node(new Type(Type::Wheat)));
			}
			else if (resourceTL == "Stone") {
				square->setTopLeft(Node(new Type(Type::Wheat)));
			}
			else {
				square->setTopLeft(Node(new Type(Type::None)));
			}

			if (resourceTR == "Wheat") {
				square->setTopRight(Node(new Type(Type::Wheat)));
			}
			else if (resourceTR == "Sheep") {
				square->setTopRight(Node(new Type(Type::Wheat)));
			}
			else if (resourceTR == "Timber") {
				square->setTopRight(Node(new Type(Type::Wheat)));
			}
			else if (resourceTR == "Stone") {
				square->setTopRight(Node(new Type(Type::Wheat)));
			}
			else {
				square->setTopRight(Node(new Type(Type::None)));
			}

			if (resourceBL == "Wheat") {
				square->setBottomLeft(Node(new Type(Type::Wheat)));
			}
			else if (resourceBL == "Sheep") {
				square->setBottomLeft(Node(new Type(Type::Wheat)));
			}
			else if (resourceBL == "Timber") {
				square->setBottomLeft(Node(new Type(Type::Wheat)));
			}
			else if (resourceBL == "Stone") {
				square->setBottomLeft(Node(new Type(Type::Wheat)));
			}
			else {
				square->setBottomLeft(Node(new Type(Type::None)));
			}

			if (resourceBR == "Wheat") {
				square->setBottomRight(Node(new Type(Type::Wheat)));
			}
			else if (resourceBR == "Sheep") {
				square->setBottomRight(Node(new Type(Type::Wheat)));
			}
			else if (resourceBR == "Timber") {
				square->setBottomRight(Node(new Type(Type::Wheat)));
			}
			else if (resourceBR == "Stone") {
				square->setBottomRight(Node(new Type(Type::Wheat)));
			}
			else {
				square->setBottomRight(Node(new Type(Type::None)));
			}

			(*gameBoard)[{x, y}] = square;
		}

		setUpAdjacencies();
	}
}

void GBMaps::saveGame() {

	ofstream output("Sample.txt");

	output << *numberOfPlayers << endl;
	output << *height << endl;
	output << *width << endl;

	iterate = begin();

	for (; iterate != gameBoard->end(); ++iterate) {
		output << iterate->second->getX() << endl;
		output << iterate->second->getY() << endl;
		output << iterate->second->getStatus() << endl;
		output << iterate->second->getTopLeft()->getTypeString() << endl;
		output << iterate->second->getTopRight()->getTypeString() << endl;
		output << iterate->second->getBottomLeft()->getTypeString() << endl;
		output << iterate->second->getBottomRight()->getTypeString() << endl;
	}

	output.close();
}

void GBMaps::loadGame() {
	ifstream inputStream("Sample.txt");

	string input;

	inputStream >> input;
	numberOfPlayers = new int(stoi(input));
	inputStream >> input;
	height = new int(stoi(input));
	inputStream >> input;
	width = new int(stoi(input));

	int elements;
	if (*numberOfPlayers == 2) {
		elements = 25;
	}
	else if (*numberOfPlayers == 3) {
		elements = 35;
	}
	else {
		elements = 45;
	}

	cout << "Number of players: " << *numberOfPlayers << endl;
	cout << "Height: " << *height << endl;
	cout << "Width: " << *width << endl;
}