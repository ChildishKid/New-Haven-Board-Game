#include <string>
#include <iostream>
using namespace std;
#include "GBMaps.h"

namespace GBMaps {

	map<pair<int, int>, Square*> setUpBoard(int numberOfPlayers) {

		map<pair<int, int>, GBMaps::Square*> gameBoard;

		if (numberOfPlayers == 2 || numberOfPlayers == 3) {

			int max_width = 5;
			int max_height = (numberOfPlayers == 2) ? 5 : 7;

			// Set up each square piece
			for (int i = 0; i < max_height; i++) {
				for (int j = 0; j < max_width; j++) {

					gameBoard[{i, j}] = new Square(i, j);
				}
			}

			// Set up adjencies
			for (int i = 0; i < max_height; i++) {
				for (int j = 0; j < max_width; j++) {

					if (!(i - 1 < 0)) {
						gameBoard[{i, j}]->addAdj(gameBoard[{(i - 1), j}]);
					}

					if (!(i + 1 > 4)) {
						gameBoard[{i, j}]->addAdj(gameBoard[{(i + 1), j}]);
					}

					if (!(j - 1 < 0)) {
						gameBoard[{i, j}]->addAdj(gameBoard[{i, (j - 1)}]);
					}

					if (!(j + 1 > 4)) {
						gameBoard[{i, j}]->addAdj(gameBoard[{i, (j + 1)}]);
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
					gameBoard[{i, j}] = new Square(i, j);
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
						gameBoard[{i, j}]->addAdj(gameBoard[{(i - 1), j}]);
					}

					if (!(i + 1 == max_height)
						&& !(i + 1 == max_height - 1 && j == 0)
						&& !(i + 1 == max_height - 1 && j == max_width - 1)) {
						gameBoard[{i, j}]->addAdj(gameBoard[{(i + 1), j}]);
					}

					if (!(j - 1 < 0)
						&& !(i == 0 && j - 1 == 0)
						&& !(i == max_height - 1 && j - 1 == 0)) {
						gameBoard[{i, j}]->addAdj(gameBoard[{i, (j - 1)}]);
					}

					if (!(j + 1 == max_width)
						&& !(i == 0 && j + 1 == max_width - 1)
						&& !(i == max_height - 1 && j + 1 == max_width - 1)) {
						gameBoard[{i, j}]->addAdj(gameBoard[{i, (j + 1)}]);
					}
				}
			}
		}
		return gameBoard;
	}

	Square::Square(int x_value, int y_value) {

		x = new int(x_value);
		y = new int(y_value);
		topLeft = new string("");
		topRight = new string("");
		bottomLeft = new string("");
		bottomRight = new string("");
		status = false;
		size = 0;
	}

	Square::~Square() {
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

	void Square::setTopLeft(string tL) {
		*topLeft = tL;
	}

	void Square::setTopRight(string tR) {
		*topRight = tR;
	}

	void Square::setBottomLeft(string bL) {
		*bottomLeft = bL;
	}

	void Square::setBottomRight(string bR) {
		*bottomRight = bR;
	}

	void Square::setX(int x_value) {
		*x = x_value;
	}

	void Square::setY(int y_value) {
		*y = y_value;
	}

	void Square::setStatus(bool value) {
		status = value;
	}

	void Square::addAdj(Square* obj) {
		adjacent.push_back(obj);
		size++;
	}

	string Square::getTopLeft() const {
		return *topLeft;
	}

	string Square::getTopRight() const {
		return *topRight;
	}

	string Square::getBottomLeft() const {
		return *bottomLeft;
	}

	string Square::getBottomRight() const {
		return *bottomRight;
	}

	vector<Square*> Square::getAdj() const {
		return adjacent;
	}

	int Square::getX() const {
		return *x;
	}

	int Square::getY() const {
		return *y;
	}

	int Square::getSize() const {
		return size;
	}
}