#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "VGMap.h"


using namespace std;

int main() {

	string name;
	cout << "Please enter your name: " << endl;
	cin >> name;

	VGMap* VG = new VGMap(name);


	for (int i = 0; i < VG->getWidth(); i++) {
		for (int j = 0; j < VG->getHeight(); j++) {
			VGMap::Circle* circle = VG->getCircle(i, j);
			cout << "(" << circle->getX() << ", " << circle->getY() << ")" << endl;
			vector<VGMap::Circle*> adj = circle->getAdj();
			cout << "Adjacencies: ";
			for (int k = 0; k < adj.size(); k++) {
				cout << "(" << adj.at(k)->getX() << ", " << adj.at(k)->getY() << ")";
			}
			cout << endl;
			cout << endl;
		}
	}

	system("pause");

	return 0;

}