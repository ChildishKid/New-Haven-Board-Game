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
		Node();

		Type getType();
		string getTypeString();
		void setType(Type* type);

	private:
		Type * type;
		friend bool operator==(const GBMaps::Node &lhs, const GBMaps::Node &rhs);
		friend bool operator!=(const GBMaps::Node &lhs, const GBMaps::Node &rhs);
	};

	class Square {
	public:
		Square(int x_value, int y_value);
		Square();
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
		bool getStatus() const;


	private:
		Node * topLeft;
		Node* topRight;
		Node* bottomLeft;
		Node* bottomRight;
		int* x;
		int* y;
		bool* status;
		vector<Square*>* adjacent;
		int* size;
	};

	GBMaps(int numOfPlayers);
	GBMaps();
	~GBMaps();

	map<pair<int, int>, Square*>::iterator iterate;
	map<pair<int, int>, Square*>::iterator begin();
	map<pair<int, int>, Square*>::iterator end();

	int getHeight();
	int getWidth();
	int getNumberOfPlayers();
	Square* getSquare(int x_value, int y_value);
	bool squareAboveExists(int x_value, int y_value);
	bool squareBelowExists(int x_value, int y_value);
	bool squareToLeftExists(int x_value, int y_value);
	bool squareToRightExists(int x_value, int y_value);

	void setHeight(int h);
	void setWidth(int w);
	void setNumberOfPlayers(int players);

private:
	map<pair<int, int>, Square*>* gameBoard;
	int* height;
	int* width;
	int* numberOfPlayers;
	void setUpBoard();
	void setUpAdjacencies();
};
