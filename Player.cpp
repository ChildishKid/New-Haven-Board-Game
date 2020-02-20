#include "Player.h"
#include <iostream>


using namespace std;


Player::Player(Deck* deck, ResourceCounter* rc, GBMaps* gboard) {
	this->playersHand = new Hand(deck,rc);
	this->playersVGMap = new VGMap();
	this->gboard = gboard;
	}

Player::Player(){

}

void Player::placeHarvestTile(int x, int y){ 
	vector<HarvestTile*> available = this->getPlayersHand().getHarvestTiles();
	cout << "Here are Harvest Tiles available for you:" << endl << endl;
	for (int i = 0; i < available.size(); i++) {
		cout << "Option " << i << ":" << endl << endl;
		cout << *(available[i]->getTopLeftNode()) << " " << *(available[i]->getTopRightNode()) << endl;
		cout << *(available[i]->getBottomLeftNode()) << " " << *(available[i]->getBottomRightNode()) << endl << endl;
	}
	cout << "Choose your option:";
	int option;
	cin >> option;

	cout << "Here are the options on how to place it:" << endl;
	for (int i = 0; i < 4; i++) {
		cout << "Option " << i << ":" << endl << endl;
		cout << *(available[option]->getTopLeftNode()) << " " << *(available[option]->getTopRightNode()) << endl;
		cout << *(available[option]->getBottomLeftNode()) << " " << *(available[option]->getBottomRightNode()) << endl << endl;
		available[option]->rotateTile();
	}

	cout << "Choose your option:";
	int rotation;
	cin >> rotation;

	for (int i = 0; i < rotation; i++) {
		available[option]->rotateTile();
	}

	GBMaps::Square* target = this->getGBoard()->getSquare(x, y);
	target->setBottomLeft(GBMaps::Node(available[option]->getBottomLeftNode()));
	target->setBottomRight(GBMaps::Node(available[option]->getBottomRightNode()));
	target->setTopLeft(GBMaps::Node(available[option]->getTopLeftNode()));
	target->setTopRight(GBMaps::Node(available[option]->getTopRightNode()));
	target->setStatus(true);
	}

Building* Player::DrawBuilding() {

	}
HarvestTile* Player::DrawHarvestTile() {

	}
map<string, int> Player::ResourceTracker() {

	}
void Player::BuildVillage(pair<int, int>) {

	}
map<string, int> Player::CalculateResources() {

	}
