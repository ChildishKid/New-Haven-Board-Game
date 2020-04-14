#pragma once
#include <map>
#include <string>
#include <vector>
#include "Resources.h"
using namespace std;

// Needed as forward reference.
class Game;
class Observable;

class IObserver {
    public:
        virtual void update(string message) = 0;
        void setObservable(Observable* obs);
        Observable* getObservable() const;
    
    private:
        Observable* observable;
};

class GameObserver : IObserver {
    public:
        GameObserver(Game* game);
        void update(string message);
};

class Observable {
    public:
        Observable();
        
        void addObserver(IObserver* obs);
        void removeObserver(IObserver* obs);
        void notify(string message);
    
    private:
        vector<IObserver*>* observers;

};
