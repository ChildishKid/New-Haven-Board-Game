#include <string>
#include <iostream>
using namespace std;
#include "GBMaps.h"

	GBMaps::Square::Square(int x_value, int y_value) {
		x = new int(x_value);
		y = new int(y_value);
		topLeft = NULL;
		topRight = NULL;
		bottomLeft = NULL;
		bottomRight = NULL;
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

	void GBMaps::Square::setTopLeft(Type tL) {
		*topLeft = tL;
	}

	void GBMaps::Square::setTopRight(Type tR) {
		*topRight = tR;
	}

	void GBMaps::Square::setBottomLeft(Type bL) {
		*bottomLeft = bL;
	}

	void GBMaps::Square::setBottomRight(Type bR) {
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

	Type GBMaps::Square::getTopLeft() const {
		return *topLeft;
	}

	Type GBMaps::Square::getTopRight() const {
		return *topRight;
	}

	Type GBMaps::Square::getBottomLeft() const {
		return *bottomLeft;
	}

	Type GBMaps::Square::getBottomRight() const {
		return *bottomRight;
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

	void GBMaps::setUpBoard(int numberOfPlayers) {

		if (numberOfPlayers == 2 || numberOfPlayers == 3) {
			int max_width = 5;
			int max_height = (numberOfPlayers == 2) ? 5 : 7;

			// Set up each square piece
			for (int i = 0; i < max_height; i++) {
				for (int j = 0; j < max_width; j++) {
					(*gameBoard)[{i, j}] = new GBMaps::Square(i, j);
				}
			}

			// Set up adjencies
			for (int i = 0; i < max_height; i++) {
				for (int j = 0; j < max_width; j++) {

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

		if (numberOfPlayers == 4) {
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

	GBMaps::GBMaps(int numberOfPlayers) {
		gameBoard = new map<pair<int, int>, Square*>();
		setUpBoard(numberOfPlayers);
		iterate = gameBoard->begin();
	}

	GBMaps::Square* GBMaps::getSquare(int x_value, int y_value) const {
		return (*gameBoard).at({ x_value, y_value });
	}

	map<pair<int, int>, GBMaps::Square*>::iterator GBMaps::begin() {
		return (*gameBoard).begin();
	}

	map<pair<int, int>, GBMaps::Square*>::iterator GBMaps::end() {
		return (*gameBoard).end();
	}