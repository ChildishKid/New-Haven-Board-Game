#pragma once

#include<iostream>
#include<cstdlib>
#include<vector>
#include<map>
#include "Resources.h"

using namespace std;

class VGMap {
public:
	class Circle {
	public:	
		Circle(int x_value, int y_value);
		Circle();
		~Circle();

		void setX(int x);
		void setY(int y);
		void setCost(int val);
		void setStatus(bool stat);
		void setBuilding(Building* b);
		void addAdj(Circle* obj);

		int getX() const;
		int getY() const;
		int getCost() const;
		bool getStatus() const;
		vector<Circle*> getAdj() const;
		Building* getBuilding() const;

	private: 
		int* x;
		int* y;
		int* cost;
		bool* status;
		vector<Circle*>* adjacent;
		Building* building;
	};

	VGMap(string player);
	VGMap();
	~VGMap();
	Circle* getCircle(int x_value, int y_value) const;
	int getWidth();
	int getHeight();
	string getPlayerName();
	

private:
	map<pair<int, int>, Circle*>* playerBoard;
	string* playerName;
	int* width;
	int* height;
	void setupBoard();
};

