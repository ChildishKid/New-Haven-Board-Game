#include "GameObservers.h"
#include <iostream>
#include <map>
#include <string>

ResourceMarkerObserver::ResourceMarkerObserver() {
    resourceMarkers = new map<Type, int>();
    (*resourceMarkers)[Type::Sheep] = 0;
    (*resourceMarkers)[Type::Wheat] = 0;
    (*resourceMarkers)[Type::Timber] = 0;
    (*resourceMarkers)[Type::Stone] = 0;
};

void ResourceMarkerObserver::update(map<Type, int>* rm, string* playerName, bool resourcesCollected) {
    cout << "~~~~~~~~~~~ RESOURCE MARKER OBSERVER ~~~~~~~~~~~" << endl;
    if (resourcesCollected) {
        cout << *playerName << " has played a harvest tile." << endl;
    } else {
        cout << *playerName << " has built a village building." << endl;
    }

    cout << "The resource markers were previously set to: " << endl;
    cout << "Sheep: " << (*resourceMarkers)[Type::Sheep] << endl;
    cout << "Wheat: " << (*resourceMarkers)[Type::Wheat] << endl;
    cout << "Timber: " << (*resourceMarkers)[Type::Timber] << endl;
    cout << "Stone: " << (*resourceMarkers)[Type::Stone] << endl;

    (*resourceMarkers)[Type::Sheep] = (*rm)[Type::Sheep];
    (*resourceMarkers)[Type::Wheat] = (*rm)[Type::Wheat];
    (*resourceMarkers)[Type::Timber] = (*rm)[Type::Timber];
    (*resourceMarkers)[Type::Stone] = (*rm)[Type::Stone];

    cout << "The resource markers have now been set to: " << endl;
    cout << "Sheep: " << (*resourceMarkers)[Type::Sheep] << endl;
    cout << "Wheat: " << (*resourceMarkers)[Type::Wheat] << endl;
    cout << "Timber: " << (*resourceMarkers)[Type::Timber] << endl;
    cout << "Stone: " << (*resourceMarkers)[Type::Stone] << endl;
    
};

VillageBuildingObserver::VillageBuildingObserver() {
    villageBuildingCount = new int(0);
};

void VillageBuildingObserver::update(string* playerName) {
    cout << "~~~~~~~~~~~ VILLAGE BUILDING OBSERVER ~~~~~~~~~~~" << endl;
    cout << *playerName << " has played a village building." << endl;
    *villageBuildingCount++;
    cout << *playerName << " has now played " << *villageBuildingCount << " buildings." << endl;
};
