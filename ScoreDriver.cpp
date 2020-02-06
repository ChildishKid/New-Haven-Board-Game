#include <iostream>
#include <map>
#include "Score.h"
using namespace std;

int main() {

    map<Type, string> enumValues = {{Type::Wheat, "Wheat"}, {Type::Stone, "Stone"}, 
        {Type::Timber, "Timber"}, {Type::Sheep, "Sheep"}};
    
    Type* sheep = new Type{Type::Sheep};
    Type* timber = new Type{Type::Timber};
    Type* wheat = new Type{Type::Wheat};
    Type* stone = new Type{Type::Stone};

    cout << "======= TEST with a 2 player game =======" << endl;
    cout << "Testing at position (4,2)" << endl;
    cout << "Expected: 10 Wheat, 1 Sheep, 3 Timber, 0 Stone" << endl;
    GBMaps* gbMap2 = new GBMaps(2);

    gbMap2->getSquare(4, 2)->getBottomLeft()->setType(sheep);
    gbMap2->getSquare(4, 2)->getTopRight()->setType(timber);
    gbMap2->getSquare(4, 2)->getTopLeft()->setType(wheat);
    gbMap2->getSquare(4, 2)->getBottomRight()->setType(timber);

    gbMap2->getSquare(4, 3)->getBottomLeft()->setType(wheat);
    gbMap2->getSquare(4, 3)->getTopRight()->setType(sheep);
    gbMap2->getSquare(4, 3)->getTopLeft()->setType(wheat);
    gbMap2->getSquare(4, 3)->getBottomRight()->setType(timber);

    gbMap2->getSquare(4, 4)->getBottomLeft()->setType(wheat);
    gbMap2->getSquare(4, 4)->getTopRight()->setType(wheat);
    gbMap2->getSquare(4, 4)->getTopLeft()->setType(wheat);
    gbMap2->getSquare(4, 4)->getBottomRight()->setType(timber);

    gbMap2->getSquare(3, 3)->getBottomLeft()->setType(wheat);
    gbMap2->getSquare(3, 3)->getTopRight()->setType(sheep);
    gbMap2->getSquare(3, 3)->getTopLeft()->setType(wheat);
    gbMap2->getSquare(3, 3)->getBottomRight()->setType(wheat);

    gbMap2->getSquare(3, 4)->getBottomLeft()->setType(wheat);
    gbMap2->getSquare(3, 4)->getTopRight()->setType(sheep);
    gbMap2->getSquare(3, 4)->getTopLeft()->setType(timber);
    gbMap2->getSquare(3, 4)->getBottomRight()->setType(sheep);

    ResourceCounter* resourceCounter = new ResourceCounter(gbMap2);
    map<Type, int*>* collectedResources = new map<Type, int*>();
    collectedResources = resourceCounter->calculateCollectedResources(4, 2);
    
    cout << "Actual: ";
    std::map<Type, int*>::iterator it = collectedResources->begin();
    while (it != collectedResources->end()) {
        Type type = it->first;
        int* count = it->second;
        cout << *count << " " << enumValues[type] << ", ";
        it++;
    }

    cout << endl << endl << "======= TEST with a 3 player game =======" << endl;
    cout << "Testing at position (6,3)" << endl;
    cout << "Expected: 6 Wheat, 3 Sheep, 1 Timber, 0 Stone" << endl;
    GBMaps* gbMap3 = new GBMaps(3);

    gbMap3->getSquare(3, 6)->getBottomLeft()->setType(wheat);
    gbMap3->getSquare(3, 6)->getTopRight()->setType(sheep);
    gbMap3->getSquare(3, 6)->getTopLeft()->setType(timber);
    gbMap3->getSquare(3, 6)->getBottomRight()->setType(sheep);

    gbMap3->getSquare(3, 5)->getBottomRight()->setType(wheat);
    gbMap3->getSquare(3, 5)->getTopLeft()->setType(wheat);
    gbMap3->getSquare(3, 5)->getBottomLeft()->setType(wheat);
    gbMap3->getSquare(3, 5)->getTopRight()->setType(sheep);

    gbMap3->getSquare(4, 5)->getBottomRight()->setType(timber);
    gbMap3->getSquare(4, 5)->getTopLeft()->setType(wheat);
    gbMap3->getSquare(4, 5)->getBottomLeft()->setType(wheat);
    gbMap3->getSquare(4, 5)->getTopRight()->setType(sheep);

    resourceCounter = new ResourceCounter(gbMap3);
    collectedResources = new map<Type, int*>();
    collectedResources = resourceCounter->calculateCollectedResources(3, 6);
    
    cout << "Actual: ";
    it = collectedResources->begin();
    while (it != collectedResources->end()) {
        Type type = it->first;
        int* count = it->second;
        cout << *count << " " << enumValues[type] << ", ";
        it++;
    }

    cout << endl << endl << "======= TEST with a 4 player game =======" << endl;
    cout << "Testing at position (1,2)" << endl;
    cout << "Expected: 0 Wheat, 5 Sheep, 0 Timber, 2 Stone" << endl;
    GBMaps* gbMap4 = new GBMaps(3);

    gbMap4->getSquare(1, 1)->getBottomLeft()->setType(sheep);
    gbMap4->getSquare(1, 1)->getTopRight()->setType(stone);
    gbMap4->getSquare(1, 1)->getTopLeft()->setType(sheep);
    gbMap4->getSquare(1, 1)->getBottomRight()->setType(wheat);

    gbMap4->getSquare(1, 2)->getBottomRight()->setType(stone);
    gbMap4->getSquare(1, 2)->getTopLeft()->setType(sheep);
    gbMap4->getSquare(1, 2)->getBottomLeft()->setType(sheep);
    gbMap4->getSquare(1, 2)->getTopRight()->setType(sheep);

    resourceCounter = new ResourceCounter(gbMap4);
    collectedResources = new map<Type, int*>();
    collectedResources = resourceCounter->calculateCollectedResources(1, 2);
    
    cout << "Actual: ";
    it = collectedResources->begin();
    while (it != collectedResources->end()) {
        Type type = it->first;
        int* count = it->second;
        cout << *count << " " << enumValues[type] << ", ";
        it++;
    }
}
