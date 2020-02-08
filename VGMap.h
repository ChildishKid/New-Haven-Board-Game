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
	public:Circle(int x_value, int y_value);
		   Circle();
		~Circle();

		void setX(int x);
		void setY(int y);
		void setColour(Type colour);
		void setCost(int val);
		void setStatus(string stat);
		void addAdj(Circle* obj);

		int getX() const;
		int getY() const;
		Type getColour() const;
		int getCost() const;
		string getStatus() const;
		vector<Circle*> getAdj() const;

	private: 
		int* x;
		int* y;
		Type* colour;
		int* cost;
		string* status;
		vector<Circle*>* adjacent;
	};

	VGMap(string player);
	VGMap();
	~VGMap();
	Circle* getCircle(int x_value, int y_value) const;
	

private:
	map<pair<int, int>, Circle*>* playerBoard;
	string playerName;
};

