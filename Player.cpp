#include "Player.h"
#include <iostream>
#include "Score.h"

using namespace std;

Player::Player(Deck* deck, ResourceCounter* rc, GBMaps* gboard) {
	this->playersHand = new Hand(deck,rc);
	this->playersVGMap = new VGMap();
	this->gboard = gboard;
}

Player::Player(string n, int i, GBMaps* gboard) {
	this->name = new string(n);
	this->id = new int(i);
	this->gboard = gboard;
}

Player::Player(){

}

void Player::placeHarvestTile(int x, int y){ 
	
	vector<HarvestTile*>* available = this->getPlayersHand()->getHarvestTiles();
	cout << "Here are Harvest Tiles available for you:" << endl << endl;
	for (int i = 0; i < available->size(); i++) {
		cout << "Option " << i << ":" << endl << endl;
		cout << *(available->at(i)->getTopLeftNode()) << " " << *(available->at(i)->getTopRightNode()) << endl;
		cout << *(available->at(i)->getBottomLeftNode()) << " " << *(available->at(i)->getBottomRightNode()) << endl << endl;
	}
	cout << "Choose your option:";
	int option;
	cin >> option;
	HarvestTile* chosen = available->at(option);
	available->erase(available->begin() + option);

	cout << "Here are the options on how to place it:" << endl;
	for (int i = 0; i < 4; i++) {
		cout << "Option " << i << " :" << endl << endl;
		cout << *(chosen->getTopLeftNode()) << " " << *(chosen->getTopRightNode()) << endl;
		cout << *(chosen->getBottomLeftNode()) << " " << *(chosen->getBottomRightNode()) << endl << endl;
		chosen->rotateTile();
	}

	cout << "Choose your option:";
	int rotation;
	cin >> rotation;

	for (int i = 0; i < rotation; i++) {
		chosen->rotateTile();
	}

	GBMaps::Square* target = this->getGBoard()->getSquare(x, y);
	target->setBottomLeft(GBMaps::Node(chosen->getBottomLeftNode()));
	target->setBottomRight(GBMaps::Node(chosen->getBottomRightNode()));
	target->setTopLeft(GBMaps::Node(chosen->getTopLeftNode()));
	target->setTopRight(GBMaps::Node(chosen->getTopRightNode()));
	target->setStatus(true);

}

void Player::placeHarvestTile(int x, int y, HarvestTile* tile) {

	GBMaps::Square* target = this->getGBoard()->getSquare(x, y);
	target->setStatus(true);
	target->getTopLeft()->setType(tile->getTopLeftNode());
	target->getTopRight()->setType(tile->getTopRightNode());
	target->getBottomLeft()->setType(tile->getBottomLeftNode());
	target->getBottomRight()->setType(tile->getBottomRightNode());
}

void Player::drawBuilding() {
	Building* drawn = static_cast<Building*>(this->getPlayersHand()->getDeck()->draw(ResourceType::Building));
	this->getPlayersHand()->getBuildings()->push_back(drawn);
}

void Player::drawHarvestTile() {
	HarvestTile* drawn = static_cast<HarvestTile*>(this->getPlayersHand()->getDeck()->draw(ResourceType::HarvestTile));
	this->getPlayersHand()->getHarvestTiles()->push_back(drawn);
}

map<string, int> Player::resourceTracker() {
	map<string, int> container;
	container.insert(pair<string, int>("Sheep", *this->getPlayersHand()->getSheepResourceMarker()));
	container.insert(pair<string, int>("Stone", *this->getPlayersHand()->getStoneResourceMarker()));
	container.insert(pair<string, int>("Timber", *this->getPlayersHand()->getTimberResourceMarker()));
	container.insert(pair<string, int>("Wheat", *this->getPlayersHand()->getWheatResourceMarker()));
	return container;
}

void Player::buildVillage(int x, int y) {
	vector<Building*>* available = this->getPlayersHand()->getBuildings();
	cout << "Here are Buildings available for you:" << endl << endl;
	for (int i = 0; i < available->size(); i++) {
		cout << "Option " << i << " :" << endl;
		cout << *(available->at(i)->getType()) << " " << *(available->at(i)->getCost()) << endl << endl;
	}
	cout << "Choose your option:";
	int option;
	cin >> option;

	cout << "Choose your cost:";
	int cost;
	cin >> cost;
	
	if (cost < *(available->at(option)->getCost())) {
		available->at(option)->setActualCost(&cost);
	}
	this->getVGMap()->getCircle(x, y)->setBuilding(available->at(option));
	this->getVGMap()->getCircle(x, y)->setCost(cost);
	this->getVGMap()->getCircle(x, y)->setStatus(true);
}

map<Type, int*>* Player::calculateResources(int x, int y) {
	return this->getPlayersHand()->getResourceCounter()->calculateCollectedResources(x, y);
}

void Player::setPlayersVGMap(VGMap* map) {
	playersVGMap = map;
}

void Player::setPlayersHand(Hand* h) {
	playersHand = h;
}

void Player::setPlayersScore(int* score) {
	finalScore = score;
}
bool Player::sortById(Player* one, Player* two) {
	return *one->getId() < *two->getId();
}