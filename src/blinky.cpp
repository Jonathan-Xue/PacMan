#include "blinky.h"

Blinky::Blinky() {}

Blinky::Blinky(vector<vector<Tile>> *b, Pacman *p) {
	board = b;
	pacman = p;
}

Blinky::~Blinky() {}

void Blinky::update() {
	// Calculate targetTile
	calculateTargetTile();

	// Update currentVelocity
	updateVelocity();

	// Move In The Direction Of currentVelocity
	move();

	// Adjust tilePosition To Stay In Bounds
	adjustBounds();
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