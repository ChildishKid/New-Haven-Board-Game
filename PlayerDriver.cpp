#include "Player.h"
#include "Score.h"

int main() {
	pair<int, int> coor(3, 5);
	Deck d = Deck();
	GBMaps gb = GBMaps();
	ResourceCounter rc = ResourceCounter(&gb);
	Player p1 = Player(&d, &rc, &gb);
	p1.placeHarvestTile(3,5);

	return 0;
}