#pragma once
#include <string>
#include <vector>
#include <map>
#include "Resources.h"
using namespace std;

class GBMaps {

public:
	class Square {
	public:
		Square(int x_value, int y_value);
		~Square();

		void setTopLeft(Type tL);
		void setTopRight(Type tR);
		void setBottomLeft(Type bL);
		void setBottomRight(Type bR);
		void setX(int x_value);
		void setY(int y_value);
		void setStatus(bool value);
		void addAdj(Square* obj);

		Type getTopLeft() const;
		Type getTopRight() const;
		Type getBottomLeft() const;
		Type getBottomRight() const;
		vector<Square*> getAdj() const;
		int getX() const;
		int getY() const;
		int getSize() const;


	private:
		Type* topLeft;
		Type* topRight;
		Type* bottomLeft;
		Type* bottomRight;
		int* x;
		int* y;
		bool* status;
		vector<Square*>* adjacent;
		int* size;

	};

	map<pair<int, int>, Square*>::iterator iterate;

	GBMaps(int numberOfPlayers);
	Square* getSquare(int x_value, int y_value) const;
	map<pair<int, int>, Square*>::iterator begin();
	map<pair<int, int>, Square*>::iterator end();

private:
	map<pair<int, int>, Square*>* gameBoard;
	void setUpBoard(int numberOfPlayers);

};