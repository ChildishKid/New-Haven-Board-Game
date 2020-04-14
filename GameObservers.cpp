#include "GameObservers.h"
#include "Game.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

Observable::Observable() {
    observers = new vector<IObserver*>();
}

void Observable::addObserver(IObserver* observer) {
    observers->push_back(observer);
};

void Observable::removeObserver(IObserver* observer) {
    for( std::vector<IObserver*>::iterator iter = observers->begin(); iter != observers->end(); ++iter ) {
        if(*iter == observer) {
            observers->erase(iter);
            break;
        }
    }
}

void Observable::notify(string message) {
    for( std::vector<IObserver*>::iterator iter = observers->begin(); iter != observers->end(); ++iter ) {
        (*iter)->update(message);
    }
}

void IObserver::setObservable(Observable* obs) {
    observable = obs;
}

Observable* IObserver::getObservable() const {
    return observable;
}

GameObserver::GameObserver(Game* obs) {
    obs->addObserver(this);
    setObservable(obs);
}

void GameObserver::update(string message) {
    cout << message << endl;
    cout << "Observer has been updated. Here is the current state of the game: " << endl;
    cout << *static_cast<Game*>(getObservable()) << endl;
}

