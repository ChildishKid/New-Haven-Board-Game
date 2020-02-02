#pragma once
#include <string>
#include <vector>
#include <map>
using namespace std;

namespace GBMaps {

	class Square {
	public:
		Square(int x_value, int y_value);
		~Square();

		void setTopLeft(string tL);
		void setTopRight(string tR);
		void setBottomLeft(string bL);
		void setBottomRight(string bR);
		void setX(int x_value);
		void setY(int y_value);
		void setStatus(bool value);
		void addAdj(Square* obj);

		string getTopLeft() const;
		string getTopRight() const;
		string getBottomLeft() const;
		string getBottomRight() const;
		vector<Square*> getAdj() const;
		int getX() const;
		int getY() const;
		int getSize() const;


	private:
		string* topLeft;
		string* topRight;
		string* bottomLeft;
		string* bottomRight;
		int* x;
		int* y;
		bool status;
		vector<Square*> adjacent;
		int size;

	};

	//typedef pair<int, int> position;
	//extern map<position, Square*> gameBoard;

	map<pair<int, int>, Square*> setUpBoard(int numberOfPlayers);
}