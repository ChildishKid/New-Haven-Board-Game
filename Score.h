#pragma once
#include <string>
#include <vector>
#include <map>
#include "GBMaps.h"
#include "VGMap.h"
using namespace std;

class ResourceCounter {

    public:
        ResourceCounter(GBMaps* gBMap);    
        GBMaps* getGBMap();
        map<Type, int*>* calculateCollectedResources(int x_value, int y_value);

    private:
        GBMaps* gbMap;
        void calculateCollectedResources2(int x_value, int y_value, Type type, GBMaps::Node* node,
            map<Type, int*>* collectedResources, vector<GBMaps::Node*>* visitedNodes);
};

class Score {
    public:
        Score(VGMap* vGMap);
        VGMap getVGMap();
        int calculateScore();

    private:
        VGMap* vgMap;
};
