#pragma once
#include <map>
#include <string>
#include "Resources.h"
using namespace std;

// Needed as forward reference.
class Game;

class ResourceMarkerObserver {
    public: 
        ResourceMarkerObserver();
        ~ResourceMarkerObserver();

        // resourcesCollected is true only after a player has played a harvest tile. Otherwise,
        // it is implied that the player has played a village building and resources have depleted.
        void update(map<Type, int>* rm, string* playerName, bool resourcesCollected);
    
    private:
        map<Type, int>* resourceMarkers;
};


class VillageBuildingObserver {
    public: 
        VillageBuildingObserver();
        ~VillageBuildingObserver();

        //increment by 1 when called and print the player's name.
        void update(string* playerName);
    
    private:
        int* villageBuildingCount;

};
