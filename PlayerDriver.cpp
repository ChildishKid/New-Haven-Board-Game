#include "Player.h"
#include "Score.h"

int main() {
	pair<int, int> coor(3, 5);
	Deck d = Deck();
	GBMaps gb = GBMaps();
	ResourceCounter rc = ResourceCounter(&gb);
	Player p1 = Player(&d, &rc, &gb);
	p1.placeHarvestTile(3,5);
	
	
	/*
	cout << "HarvestTiles before: " << p1.getPlayersHand()->getHarvestTiles()->size() << endl;
	p1.DrawHarvestTile();
	cout << "HarvestTiles after: " << p1.getPlayersHand()->getHarvestTiles()->size() << endl;
	cout << "Buildings before: " << p1.getPlayersHand()->getBuildings()->size() << endl;
	p1.DrawBuilding();
	cout << "Buildings after: "  << p1.getPlayersHand()->getBuildings()->size() << endl;
	map<string, int> testmap = p1.ResourceTracker();
	cout << "ResourceTracker test:" << endl;
	for (auto it = testmap.cbegin(); it != testmap.cend(); ++it)
	{
		std::cout << it->first << " " << it->second << endl;
	}
	cout << "Before: " ;
	printf(p1.getVGMap()->getCircle(1, 1)->getStatus() ? "true \n" : "false \n");
	p1.BuildVillage(1, 1);
	cout << "After: ";
	printf(p1.getVGMap()->getCircle(1, 1)->getStatus() ? "true \n" : "false \n");
	map<Type, int*> testmap1 = *p1.CalculateResources(0,0);
	for (auto it = testmap1.cbegin(); it != testmap1.cend(); ++it)
	{
		std::cout << it->first << " " << *it->second << endl;
	}*/
	return 0;
}