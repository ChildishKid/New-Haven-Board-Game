#include <iostream>
#include "Score.h"
#include "Resources.cpp"

int main() {
    Deck* deck = new Deck();
    GBMaps* gbMap = new GBMaps(2);
    ResourceCounter* resourceCounter = new ResourceCounter(gbMap);
    Hand* hand = new Hand(deck, resourceCounter);
}