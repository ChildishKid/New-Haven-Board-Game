#pragma once
#include "Display.h"
#include <map>
#include <string>
#include <vector>

using namespace std;

// Needed as forward reference.
class Game;
//class Observable;

class Observer {
public:
	~Observer();
	virtual void update(Player* player, string message) = 0;
protected:
	Observer();
};

class Observable {
public:
	Observable();
	~Observable();
	virtual void attach(Observer* obs);
	virtual void detach(Observer* obs);
	virtual void notify(Player* player, string message);

private:
	vector<Observer*>* observers;

};

class GameObserver : public Observer {
public:
	GameObserver();
	GameObserver(Game* game);
	~GameObserver();
	void update(Player* player, string message);
	void display();
private:
	Game* subject;
};

class TurnObserver : public Observer {
public:
	TurnObserver();
	TurnObserver(Game* game);
	~TurnObserver();
	void update(Player* player, string message);
	void display(Player* player, string message);
private:
	Game* subject;
};

class GameStatisticsObserver : public Observer {
public:
	GameStatisticsObserver();
	GameStatisticsObserver(Game* game);
	~GameStatisticsObserver();
	void update(Player* player, string message);
	void display(string message);
private:
	Game* subject;
};

