#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <stdlib.h>
#include "Score.h"
#include <iostream>
using namespace std;


ResourceCounter::ResourceCounter(GBMaps* gameMap) {
    gbMap = gameMap;
};

GBMaps* ResourceCounter::getGBMap() {
    return gbMap;
}

map<Type, int*>* ResourceCounter::calculateCollectedResources(int x_value, int y_value) {

    GBMaps::Square* square = getGBMap()->getSquare(x_value, y_value);
    // 0) Initialize required pointers
    map<Type, int*>* collectedResources = new map<Type, int*>();
    vector<GBMaps::Node*>* visitedNodes = new vector<GBMaps::Node*>();
    // 1) Find adjacent nodes of top left node
    // 1.a) Set node as visited
    visitedNodes->push_back(square->getTopLeft());
    // 1.b) Add to map if doesn't exist and initialize with value 1, otherwise add 1 to value
    if (collectedResources->find(square->getTopLeft()->getType()) == collectedResources->end()) {
        (*collectedResources)[square->getTopLeft()->getType()] = new int(1);
    } else {
        (*collectedResources)[square->getTopLeft()->getType()] = new int(*((*collectedResources)[square->getTopLeft()->getType()]) + 1);
    }
    // 1.c) Check if square to left of top left node exists
    if (getGBMap()->squareToLeftExists(x_value, y_value)) {
        // If top right node of square to the left has not been visited, visit it
        if (find(visitedNodes->begin(), visitedNodes->end(), getGBMap()->getSquare(x_value - 1, y_value)->getTopRight()) == visitedNodes->end()) {
            calculateCollectedResources2(x_value - 1, y_value, square->getTopLeft()->getType(), getGBMap()->getSquare(x_value - 1, y_value)->getTopRight(), 
                collectedResources, visitedNodes);
        }
    }
    // 1.d) Check if square above of top left node exists
    if (getGBMap()->squareAboveExists(x_value, y_value)) {
        // If bottom left node of square above has not been visited, visit it
        if (find(visitedNodes->begin(), visitedNodes->end(), getGBMap()->getSquare(x_value, y_value + 1)->getBottomLeft()) == visitedNodes->end()) {
            calculateCollectedResources2(x_value, y_value + 1, square->getTopLeft()->getType(), getGBMap()->getSquare(x_value, y_value + 1)->getBottomLeft(),
                collectedResources, visitedNodes);
        }
    }

    // 2) Find adjcant nodes of top right node
    // 2.a) Set node as visited
    visitedNodes->push_back(square->getTopRight());
    // 2.b) Add to map if doesn't exist and initialize with value 1, otherwise add 1 to value
    if (collectedResources->find(square->getTopRight()->getType()) == collectedResources->end()) {
        (*collectedResources)[square->getTopRight()->getType()] = new int(1);
    } else {
        (*collectedResources)[square->getTopRight()->getType()] = new int(*(*collectedResources)[square->getTopRight()->getType()] + 1);
    }
    // 2.c) Check if square to right of top right node exists
    if (getGBMap()->squareToRightExists(x_value, y_value)) {
        // If top left node of square to the right has not been visited, visit it
        if (find(visitedNodes->begin(), visitedNodes->end(), getGBMap()->getSquare(x_value + 1, y_value)->getTopLeft()) == visitedNodes->end()) {
            calculateCollectedResources2(x_value + 1, y_value, square->getTopRight()->getType(), getGBMap()->getSquare(x_value + 1, y_value)->getTopLeft(),
                collectedResources, visitedNodes);
        }
    }
    // 2.d) Check if square above of top right node exists
    if (getGBMap()->squareAboveExists(x_value, y_value)) {
        // If bottom right node of square above has not been visited, visit it
        if (find(visitedNodes->begin(), visitedNodes->end(), getGBMap()->getSquare(x_value, y_value + 1)->getBottomRight()) == visitedNodes->end()) {
            calculateCollectedResources2(x_value, y_value + 1, square->getTopRight()->getType(), getGBMap()->getSquare(x_value, y_value + 1)->getBottomRight(),
                collectedResources, visitedNodes);
        }
    }

    // 3) Find adjacent nodes of bottom left node
    // 3.a) Set node as visited
    visitedNodes->push_back(square->getBottomLeft());
    // 3.b) Add to map if doesn't exist and initialize with value 1, otherwise add 1 to value
    if (collectedResources->find(square->getBottomLeft()->getType()) == collectedResources->end()) {
        (*collectedResources)[square->getBottomLeft()->getType()] = new int(1);
    } else {
        (*collectedResources)[square->getBottomLeft()->getType()] = new int(*(*collectedResources)[square->getBottomLeft()->getType()] + 1);
    }
    // 3.c) Check if square to left of bottom left node exists
    if (getGBMap()->squareToLeftExists(x_value, y_value)) {
        // If bottom right node of square to the left has not been visited, visit it
        if (find(visitedNodes->begin(), visitedNodes->end(), getGBMap()->getSquare(x_value - 1, y_value)->getBottomRight()) == visitedNodes->end()) {
            calculateCollectedResources2(x_value - 1, y_value, square->getBottomLeft()->getType(), getGBMap()->getSquare(x_value - 1, y_value)->getBottomRight(),
                collectedResources, visitedNodes);
        }
    }
    // 3.d) Check if square below of bottom left node exists
    if (getGBMap()->squareBelowExists(x_value, y_value)) {
        // If top right node of square below has not been visited, visit it
        if (find(visitedNodes->begin(), visitedNodes->end(), getGBMap()->getSquare(x_value, y_value - 1)->getTopLeft()) == visitedNodes->end()) {
            calculateCollectedResources2(x_value, y_value - 1, square->getBottomLeft()->getType(), getGBMap()->getSquare(x_value, y_value - 1)->getTopLeft(),
                collectedResources, visitedNodes);
        }
    }

    // 4) Find adjacent nodes of bottom right node
    // 4.a) Set node as visited
    visitedNodes->push_back(square->getBottomRight());
    // 4.b) Add to map if doesn't exist and initialize with value 1, otherwise add 1 to value
    if (collectedResources->find(square->getBottomRight()->getType()) == collectedResources->end()) {
        (*collectedResources)[square->getBottomRight()->getType()] = new int(1);
    } else {
        (*collectedResources)[square->getBottomRight()->getType()] = new int(*(*collectedResources)[square->getBottomRight()->getType()] + 1);
    }
    // 4.c) Check if square to the right of bottom right node exists
    if (getGBMap()->squareToRightExists(x_value, y_value)) {
        // If bottom left node of square to the right has not been visited, visit it
        if (find(visitedNodes->begin(), visitedNodes->end(), getGBMap()->getSquare(x_value + 1, y_value)->getBottomLeft()) == visitedNodes->end()) {
            calculateCollectedResources2(x_value + 1, y_value, square->getBottomRight()->getType(), getGBMap()->getSquare(x_value + 1, y_value)->getBottomLeft(),
                collectedResources, visitedNodes);
        }
    }
    // 4.d) Check if square below of bottom right node exists
    if (getGBMap()->squareBelowExists(x_value, y_value)) {
        // If top right node of square below has not been visited, visit it
        if (find(visitedNodes->begin(), visitedNodes->end(), getGBMap()->getSquare(x_value, y_value - 1)->getTopRight()) == visitedNodes->end()) {
            calculateCollectedResources2(x_value, y_value - 1, square->getBottomRight()->getType(), getGBMap()->getSquare(x_value, y_value - 1)->getTopRight(),
                collectedResources, visitedNodes);
        }
    }

    return collectedResources;
};

void ResourceCounter::calculateCollectedResources2(int x_value, int y_value, Type type, GBMaps::Node* node, 
    map<Type, int*>* collectedResources, vector<GBMaps::Node*>* visitedNodes) {

    GBMaps::Square* square = getGBMap()->getSquare(x_value, y_value);
    visitedNodes->push_back(node);

    // Only continue if the node has the specified type, else do nothing
    if (node->getType() == type) {
        // Step 1: Add 1 to value of type
        (*collectedResources)[node->getType()] = new int(*(*collectedResources)[node->getType()] + 1);
        // Step 2: Find which node in square the visited node is and then visit adjacent nodes
        // If top left node...
        if (square->getTopLeft() == node) {
            // if top right node has not been visited, visit it
            if (square->getTopRight()->getType() == type && 
                find(visitedNodes->begin(), visitedNodes->end(), square->getTopRight()) == visitedNodes->end()) {
                calculateCollectedResources2(x_value, y_value, type, square->getTopRight(), collectedResources, visitedNodes);
            }
            // if bottom left node has not been visited, visit it
            if (square->getBottomLeft()->getType() == type && 
                find(visitedNodes->begin(), visitedNodes->end(), square->getBottomLeft()) == visitedNodes->end()) {
                calculateCollectedResources2(x_value, y_value, type, square->getBottomLeft(), collectedResources, visitedNodes);
            }

            // if square above exists...
            if (getGBMap()->squareAboveExists(x_value, y_value)) {
                // if bottom left node of square above has not been visited, visit it
                if (getGBMap()->getSquare(x_value, y_value + 1)->getBottomLeft()->getType() == type && 
                    find(visitedNodes->begin(), visitedNodes->end(), getGBMap()->getSquare(x_value, y_value + 1)->getBottomLeft()) == visitedNodes->end()) {
                    calculateCollectedResources2(x_value, y_value + 1, type, getGBMap()->getSquare(x_value, y_value + 1)->getBottomLeft(), collectedResources, visitedNodes);
                }
            }

            // if square to the left exists...
            if (getGBMap()->squareToLeftExists(x_value, y_value)) {
                // if top right node of square to the left has not been visited, visit it
                if (getGBMap()->getSquare(x_value - 1, y_value)->getTopRight()->getType() == type && 
                    find(visitedNodes->begin(), visitedNodes->end(), getGBMap()->getSquare(x_value - 1, y_value)->getTopRight()) == visitedNodes->end()) {
                    calculateCollectedResources2(x_value - 1, y_value, type, getGBMap()->getSquare(x_value - 1, y_value)->getTopRight(), collectedResources, visitedNodes);
                }
            }
        }

        // If top right node...
        if (square->getTopRight() == node) {
            // if top left node has not been visited, visit it
            if (square->getTopLeft()->getType() == type && 
                find(visitedNodes->begin(), visitedNodes->end(), square->getTopLeft()) == visitedNodes->end()) {
                calculateCollectedResources2(x_value, y_value, type, square->getTopLeft(), collectedResources, visitedNodes);
            }
            // if bottom right node has not been visited, visit it
            if (square->getBottomRight()->getType() == type && 
                find(visitedNodes->begin(), visitedNodes->end(), square->getBottomRight()) == visitedNodes->end()) {
                calculateCollectedResources2(x_value, y_value, type, square->getBottomRight(), collectedResources, visitedNodes);
            }

            // if square above exists...
            if (getGBMap()->squareAboveExists(x_value, y_value)) {
                // if bottom right node of square above has not been visited, visit it
                if (getGBMap()->getSquare(x_value, y_value + 1)->getBottomRight()->getType() == type && 
                    find(visitedNodes->begin(), visitedNodes->end(), getGBMap()->getSquare(x_value, y_value + 1)->getBottomRight()) == visitedNodes->end()) {
                    calculateCollectedResources2(x_value, y_value + 1, type, getGBMap()->getSquare(x_value, y_value + 1)->getBottomRight(), collectedResources, visitedNodes);
                }
            }

            // if square to the right exists...
            if (getGBMap()->squareToRightExists(x_value, y_value)) {
                // if top left node of square to right has not been visited, visit it
                if (getGBMap()->getSquare(x_value + 1, y_value)->getTopLeft()->getType() == type && 
                    find(visitedNodes->begin(), visitedNodes->end(), getGBMap()->getSquare(x_value + 1, y_value)->getTopLeft()) == visitedNodes->end()) {
                    calculateCollectedResources2(x_value + 1, y_value, type, getGBMap()->getSquare(x_value + 1, y_value)->getTopLeft(), collectedResources, visitedNodes);
                }
            }
        }

        // If bottom left node...
        if (square->getBottomLeft() == node) {
            // if top left node has not been visited, visit it
            if (square->getTopLeft()->getType() == type && 
                find(visitedNodes->begin(), visitedNodes->end(), square->getTopLeft()) == visitedNodes->end()) {
                calculateCollectedResources2(x_value, y_value, type, square->getTopLeft(), collectedResources, visitedNodes);
            }
            // if bottom right node has not been visited, visit it
            if (square->getBottomRight()->getType() == type && 
                find(visitedNodes->begin(), visitedNodes->end(), square->getBottomRight()) == visitedNodes->end()) {
                calculateCollectedResources2(x_value, y_value, type, square->getBottomRight(), collectedResources, visitedNodes);
            }

            // if square below exists...
            if (getGBMap()->squareBelowExists(x_value, y_value)) {
                // if top left node of square below has not been visited, visit it
                if (getGBMap()->getSquare(x_value, y_value - 1)->getTopLeft()->getType() == type && 
                    find(visitedNodes->begin(), visitedNodes->end(), getGBMap()->getSquare(x_value, y_value - 1)->getTopLeft()) == visitedNodes->end()) {
                    calculateCollectedResources2(x_value, y_value - 1, type, getGBMap()->getSquare(x_value, y_value - 1)->getTopLeft(), collectedResources, visitedNodes);
                }
            }

            // if square to the left exists...
            if (getGBMap()->squareToLeftExists(x_value, y_value)) {
                // if bottom right node of square to left has not been visited, visit it
                if (getGBMap()->getSquare(x_value - 1, y_value)->getBottomRight()->getType() == type && 
                    find(visitedNodes->begin(), visitedNodes->end(), getGBMap()->getSquare(x_value - 1, y_value)->getBottomRight()) == visitedNodes->end()) {
                    calculateCollectedResources2(x_value - 1, y_value, type, getGBMap()->getSquare(x_value - 1, y_value)->getBottomRight(), collectedResources, visitedNodes);
                }
            }
        }

        // If bottom right node...
        if (square->getBottomRight() == node) {
            // if top right node has not been visited, visit it
            if (square->getTopRight()->getType() == type && 
                find(visitedNodes->begin(), visitedNodes->end(), square->getTopRight()) == visitedNodes->end()) {
                calculateCollectedResources2(x_value, y_value, type, square->getTopRight(), collectedResources, visitedNodes);
            }
            // if bottom left node has not been visited, visit it
            if (square->getBottomLeft()->getType() == type && 
                find(visitedNodes->begin(), visitedNodes->end(), square->getBottomLeft()) == visitedNodes->end()) {
                calculateCollectedResources2(x_value, y_value, type, square->getBottomLeft(), collectedResources, visitedNodes);
            }

            // if square below exists...
            if (getGBMap()->squareBelowExists(x_value, y_value)) {
                // if top right node of square below has not been visited, visit it
                if (getGBMap()->getSquare(x_value, y_value - 1)->getTopRight()->getType() == type && 
                    find(visitedNodes->begin(), visitedNodes->end(), getGBMap()->getSquare(x_value, y_value - 1)->getTopRight()) == visitedNodes->end()) {
                    calculateCollectedResources2(x_value, y_value - 1, type, getGBMap()->getSquare(x_value, y_value - 1)->getTopRight(), collectedResources, visitedNodes);
                }
            }

            // if square to the right exists...
            if (getGBMap()->squareToRightExists(x_value, y_value)) {
                // if bottom left node of square to right has not been visited, visit it
                if (getGBMap()->getSquare(x_value + 1, y_value)->getBottomLeft()->getType() == type && 
                    find(visitedNodes->begin(), visitedNodes->end(), getGBMap()->getSquare(x_value + 1, y_value)->getBottomLeft()) == visitedNodes->end()) {
                    calculateCollectedResources2(x_value + 1, y_value, type, getGBMap()->getSquare(x_value + 1, y_value)->getBottomLeft(), collectedResources, visitedNodes);
                }
            }
        }
    } 
};
