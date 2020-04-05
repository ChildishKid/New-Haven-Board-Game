#include "Player.h"
#include <iostream>
#include "Score.h"
#include "Resources.h"

using namespace std;

Player::Player(string n, int i, GBMaps* gboard) {
	this->name = new string(n);
	this->id = new int(i);
	this->gboard = gboard;
	this->hasBuilt = new map<Type, bool>;
	this->hasBuilt->insert(pair<Type, bool>(Type::Wheat, false));
	this->hasBuilt->insert(pair<Type, bool>(Type::Stone, false));
	this->hasBuilt->insert(pair<Type, bool>(Type::Timber, false));
	this->hasBuilt->insert(pair<Type, bool>(Type::Sheep, false));
	this->playersHand = new Hand();
	this->finalScore = new int(0);
	this->playersVGMap = new VGMap();
}

Player::Player(){
	this->name = new string("");
	this->id = new int(0);
	this->gboard = new GBMaps();
	this->hasBuilt = new map<Type, bool>;
	this->hasBuilt->insert(pair<Type, bool>(Type::Wheat, false));
	this->hasBuilt->insert(pair<Type, bool>(Type::Stone, false));
	this->hasBuilt->insert(pair<Type, bool>(Type::Timber, false));
	this->hasBuilt->insert(pair<Type, bool>(Type::Sheep, false));
	this->playersHand = new Hand();
	this->finalScore = new int(0);
	this->playersVGMap = new VGMap();
}

Player::~Player() {
	delete(name);
	delete(id);
	delete(gboard);
	delete(hasBuilt);
	delete(playersHand);
	delete(finalScore);
	delete(playersVGMap);

	name = NULL;
	id = NULL;
	gboard = NULL;
	hasBuilt = NULL;
	playersHand = NULL;
	finalScore = NULL;
	playersVGMap = NULL;
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

void Player::buildVillage(map<Type, int>* resources) {
	string reply;
	cout << "Do you want to build a village?(Y/N)" << endl;
	cin >> reply;

	if (reply == "Y" || reply == "y") {

		//ask for location
		int x;
		int y;
		cout << "Where do you want to place new Village:\n";
		cout << "X = ";
		cin >> x;
		cout << "\nY = ";
		cin >> y;
		
		//check if space exists
		while (this->playersVGMap->getHeight()<=y || this->playersVGMap->getWidth() <= y) {
			cout << "This location doesn't exist. Please select new one:\n";
			cout << "X = ";
			cin >> x;
			cout << "\nY = ";
			cin >> y;
		}

		//check if space is empty
		while (this->playersVGMap->getCircle(x, y)->getStatus() == true) {
			cout << "This location is already in use. Please select new one:\n";
			cout << "X = ";
			cin >> x;
			cout << "\nY = ";
			cin >> y;
		}

		//ask what building user wants to use
		vector<Building*>* available = this->getPlayersHand()->getBuildings();
		cout << "Choose your building number:";
		int option;
		cin >> option;

		//check if its the first placement of this type
		bool firstplacement = this->hasBuilt->find(*(available->at(option)->getType()))->second == false;

		//check if its no the first placement of this type and its not next to same type building
		while (!firstplacement && !this->getVGMap()->getCircle(x, y)->validateCircle(*(available->at(option)->getType()))) {
			cout << "This type has been built already somewhere else. Please select new location adjecent to it:\n";
			cout << "X = ";
			cin >> x;
			cout << "\nY = ";
			cin >> y;
		}
		bool invalid_cost = true;
		int cost;
		do {
			cout << "Choose your cost:";

			cin >> cost;


			if (cost > resources->find(*(available->at(option)->getType()))->second || cost < 1) {
				cout << "You don't have enough resources, please try again: \n";
				
			}
			else {
				resources->find(*(available->at(option)->getType()))->second -= cost;
				invalid_cost = false;
			}
		} while (invalid_cost);
		if (cost != *(available->at(option)->getCost())) {
			available->at(option)->setActualCost(&cost);
		}
		this->getVGMap()->getCircle(x, y)->setBuilding(available->at(option));
		this->getVGMap()->getCircle(x, y)->setCost(cost);
		this->getVGMap()->getCircle(x, y)->setStatus(true);

		//erase building from available
		this->getPlayersHand()->getBuildings()->erase(this->getPlayersHand()->getBuildings()->begin() + option);
	}
}

void Player::buildVillage(int x, int y, int cost, int pick, string option) {
	
	getVGMap()->getCircle(x, y)->setBuilding(getPlayersHand()->getBuildings()->at(pick));
	getVGMap()->getCircle(x, y)->setStatus(true);

	if (option == "Down") {
			getVGMap()->getCircle(x, y)->getBuilding()->setActualCost(new int(cost));
	}

	getPlayersHand()->getBuildings()->erase(getPlayersHand()->getBuildings()->begin() + pick);
}

map<Type, int*>* Player::calculateResources(int x, int y) {
	return this->getPlayersHand()->getResourceCounter()->calculateCollectedResources(x, y);
}

void Player::setPlayersVGMap(VGMap* map) {
	delete playersVGMap;
	playersVGMap = map;
}

void Player::setPlayersHand(Hand* h) {
	delete playersHand;
	playersHand = h;
}

void Player::setPlayersScore(int* score) {
	*finalScore = *score;
}

bool Player::sortById(Player* one, Player* two) {
	return *one->getId() < *two->getId();
}