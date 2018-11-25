#include "blinky.h"

Blinky::Blinky() {}

Blinky::Blinky(vector<vector<Tile>> *b, Pacman *p) {
	board = b;
	pacman = p;
}

Blinky::~Blinky() {}

void Blinky::calculateTargetTile() {
	if (mode == CHASE) {
		targetTile = (*pacman).getTilePosition();
	}
	else if (mode == SCATTER) {
		targetTile = homeTilePosition;
	}
	else if (mode == FRIGHTENED) {
		// Do Nothing
	}
	else {
		std::cerr << "Error. State Is Invalid" << std::endl;
		exit(1);
	}
}