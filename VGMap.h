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
		void setType(Type type);
		void setCost(int val);
		void setStatus(string stat);
		void addAdj(Circle* obj);

		int getX() const;
		int getY() const;
		Type getType() const;
		int getCost() const;
		string getStatus() const;
		vector<Circle*> getAdj() const;

	private: 
		int* x;
		int* y;
		Type* type;
		int* cost;
		string* status;
		vector<Circle*>* adjacent;
	};

	VGMap(string player);
	VGMap();
	~VGMap();
	Circle* getCircle(int x_value, int y_value) const;
	int getWidth();
	int getHeight();
	

private:
	map<pair<int, int>, Circle*>* playerBoard;
	string* playerName;
	int* width;
	int* height;
};

