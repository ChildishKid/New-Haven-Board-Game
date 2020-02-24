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
	vector<HarvestTile*> available = this->getPlayersHand()->getHarvestTiles();
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
		cout << "Option " << i << " :" << endl << endl;
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

//need to figure out how to cast from Resource to Building
void Player::DrawBuilding() {
	Building* drawn = static_cast<Building*>(this->getPlayersHand()->getDeck()->draw(ResourceType::Building));
	this->getPlayersHand()->getBuildings().push_back(drawn);
	}

//need to figure out how to cast from Resource to HarvestTile
void Player::DrawHarvestTile() {
	HarvestTile* drawn = static_cast<HarvestTile*>(this->getPlayersHand()->getDeck()->draw(ResourceType::HarvestTile));
	this->getPlayersHand()->getHarvestTiles().push_back(drawn);
	}

map<string, int> Player::ResourceTracker() {
	map<string, int> container;
	container.insert(pair<string, int>("Sheep", *this->getPlayersHand()->getSheepResourceMarker()));
	container.insert(pair<string, int>("Stone", *this->getPlayersHand()->getStoneResourceMarker()));
	container.insert(pair<string, int>("Timber", *this->getPlayersHand()->getTimberResourceMarker()));
	container.insert(pair<string, int>("Wheat", *this->getPlayersHand()->getWheatResourceMarker()));
	return container;
	}

void Player::BuildVillage(int x, int y) {
	vector<Building*> available = this->getPlayersHand()->getBuildings();
	cout << "Here are Buildings available for you:" << endl << endl;
	for (int i = 0; i < available.size(); i++) {
		cout << "Option " << i << " :" << endl;
		cout << *(available[i]->getType()) << " " << *(available[i]->getCost()) << endl << endl;
	}
	cout << "Choose your option:";
	int option;
	cin >> option;

	cout << "Choose your cost:";
	int cost;
	cin >> cost;
	
	if (cost < *(available[option]->getCost())) {
		available[option]->setActualCost(&cost);
	}
	this->getVGMap()->getCircle(x, y)->setBuilding(available[option]);
	this->getVGMap()->getCircle(x, y)->setCost(cost);
	}

map<Type, int*>* Player::CalculateResources(int x, int y) {
	return this->getPlayersHand()->getResourceCounter()->calculateCollectedResources(x, y);
	}
