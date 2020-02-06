#pragma once
#include <string>
#include <vector>
#include <map>
#include "Resources.h"
using namespace std;

class GBMaps {

	public:
		class Node {
			public:
				Node(Type* type);
				Type getType();
				void setType(Type* type);

			private:
				Type* type;
				friend bool operator==(const GBMaps::Node &lhs, const GBMaps::Node &rhs);
				friend bool operator!=(const GBMaps::Node &lhs, const GBMaps::Node &rhs);
		};

		class Square {
			public:
				Square(int x_value, int y_value);
				~Square();

				void setTopLeft(Node tL);
				void setTopRight(Node tR);
				void setBottomLeft(Node bL);
				void setBottomRight(Node bR);
				void setX(int x_value);
				void setY(int y_value);
				void setStatus(bool value);
				void addAdj(Square* obj);

				Node* getTopLeft();
				Node* getTopRight();
				Node* getBottomLeft();
				Node* getBottomRight();
				vector<Square*> getAdj() const;
				int getX() const;
				int getY() const;
				int getSize() const;


			private:
				Node* topLeft;
				Node* topRight;
				Node* bottomLeft;
				Node* bottomRight;
				int* x;
				int* y;
				bool* status;
				vector<Square*>* adjacent;
				int* size;
		};

		map<pair<int, int>, Square*>::iterator iterate;

		GBMaps(int numOfPlayers);
		Square* getSquare(int x_value, int y_value);
		map<pair<int, int>, Square*>::iterator begin();
		map<pair<int, int>, Square*>::iterator end();
		int getHeight();
		int getWidth();
		int getNumberOfPlayers();
		bool squareAboveExists(int x_value, int y_value);
		bool squareBelowExists(int x_value, int y_value);
		bool squareToLeftExists(int x_value, int y_value);
		bool squareToRightExists(int x_value, int y_value);

	private:
		map<pair<int, int>, Square*>* gameBoard;
		int* height;
		int* width;
		int* numberOfPlayers;
		void setUpBoard();
};