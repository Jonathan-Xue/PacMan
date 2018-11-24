#include "blinky.h"

Blinky::Blinky() {}

Blinky::Blinky(Pacman *p) {
	pacman = p;
}

Blinky::~Blinky() {}

void Blinky::update(vector<vector<Tile>> board) {
	// Calculate targetTile
	calculateTargetTile();

	// Update currentVelocity
	updateVelocity(board);

	// Move In The Direction Of currentVelocity
	move();

	// Adjust tilePosition To Stay In Bounds
	adjustBounds(board);
}

void Blinky::calculateTargetTile() {
	if (mode == CHASE) {
		targetTile = (*pacman).getTilePosition();
	}
	else if (mode == SCATTER) {
		targetTile = homeTilePosition;
	}
	else if (mode == FRIGHTENED) {

	}
	else {
		std::cerr << "Error. State Is Invalid" << std::endl;
		exit(1);
	}
}