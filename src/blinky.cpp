#include "blinky.h"

Blinky::Blinky() {}

Blinky::Blinky(vector<vector<Tile>> *b, Pacman *p) {
	ghostType = BLINKY;
	defaultColor = ofColor(255, 0, 0);
	board = b;
	pacman = p;
}

Blinky::~Blinky() {}

void Blinky::calculateTargetTile() {
	if (mode == CHASE) {
		targetTile = pacman->getTilePosition();
	}
	else if (mode == SCATTER) {
		targetTile = homeTilePosition;
	}
	else if (mode == FRIGHTENED) {
		// Do Nothing (targetTile Adjustment Is For Display Debugging Purposes)
		targetTile = vector<int>{ 0, 0 };
	}
	else {
		std::cerr << "Error. State Is Invalid" << std::endl;
		exit(1);
	}
}