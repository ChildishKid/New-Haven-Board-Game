#include <iostream>
#include <map>
#include "Score.h"
#include "Resources.cpp"
using namespace std;

int main() {

    map<Type, string> enumValues = {{Type::Wheat, "Wheat"}, {Type::Stone, "Stone"}, 
        {Type::Timber, "Timber"}, {Type::Sheep, "Sheep"}};
    
    Type* sheep = new Type{Type::Sheep};
    Type* timber = new Type{Type::Timber};
    Type* wheat = new Type{Type::Wheat};
    Type* stone = new Type{Type::Stone};

    cout << "================================== RESOURCE COUNTER TESTS ==================================" << endl;
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

    cout << endl << endl << "============================ SCORE TESTS ============================" << endl;
    VGMap* vgmap = new VGMap();
    Score* score = new Score(vgmap);

    cout << endl << "============= No building test =============" << endl;
    cout << "Expected score: 0" << endl;
    cout << "Actual score: " << score->calculateScore() << endl;

    int* cost1 = new int(1);
    int* cost2 = new int(2);
    int* cost3 = new int(3);
    int* cost4 = new int(4);
    int* cost5 = new int(5);
    int* cost6 = new int(6);

    Building* building1 = new Building(wheat, cost1);
    Building* building2 = new Building(wheat, cost2);
    Building* building3 = new Building(wheat, cost3);
    Building* building4 = new Building(wheat, cost4);
    Building* building5 = new Building(wheat, cost5);
    Building* building6 = new Building(wheat, cost6);

    vgmap->getCircle(0,0)->setBuilding(building1);
    vgmap->getCircle(0,1)->setBuilding(building2);
    vgmap->getCircle(0,2)->setBuilding(building3);
    vgmap->getCircle(0,3)->setBuilding(building4);
    vgmap->getCircle(0,4)->setBuilding(building5);
    vgmap->getCircle(0,5)->setBuilding(building6);

    cout << endl << "============= First column filled for double points =============" << endl;
    cout << "Expected score: 10" << endl;
    cout << "Actual score: " << score->calculateScore() << endl;

    Building* building7 = new Building(wheat, cost6);
    building7->setActualCost(new int(2));
    vgmap->getCircle(0,3)->setBuilding(building7);

    cout << endl << "============= First column filled for no double points =============" << endl;
    cout << "Expected score: 5" << endl;
    cout << "Actual score: " << score->calculateScore() << endl;

    Building* building8 = new Building(timber, cost6);
    Building* building9 = new Building(sheep, cost6);
    Building* building10 = new Building(stone, cost6);
    Building* building11 = new Building(stone, cost6);
    Building* building12 = new Building(stone, cost1);
    Building* building13 = new Building(stone, cost2);
    Building* building14 = new Building(stone, cost3);
    Building* building15 = new Building(stone, cost4);
    building15->setActualCost(new int(1));
    Building* building16 = new Building(stone, cost5);
    Building* building17 = new Building(stone, cost1);
    Building* building18 = new Building(stone, cost1);

    vgmap->getCircle(1, 5)->setBuilding(building8);
    vgmap->getCircle(2, 5)->setBuilding(building9);
    vgmap->getCircle(3, 5)->setBuilding(building10);
    vgmap->getCircle(4, 5)->setBuilding(building11);
    vgmap->getCircle(3, 0)->setBuilding(building12);
    vgmap->getCircle(3, 1)->setBuilding(building13);
    vgmap->getCircle(3, 2)->setBuilding(building14);
    vgmap->getCircle(3, 3)->setBuilding(building15);
    vgmap->getCircle(3, 4)->setBuilding(building16);
    vgmap->getCircle(3, 0)->setBuilding(building17);
    vgmap->getCircle(4, 0)->setBuilding(building18);

    cout << endl << "============= Simulated end game =============" << endl;
    cout << "Expected score: 21" << endl;
    cout << "Actual score: " << score->calculateScore() << endl;

    system("pause");
}
