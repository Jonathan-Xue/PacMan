#include "blinky.h"

// Constructors
Blinky::Blinky() {}

Blinky::~Blinky() {}

// Methods
void Blinky::update(vector<vector<Tile>> board, Pacman pacman) {
	// Calculate targetTile
	calculateTargetTile(pacman);

	// Update currentVelocity
	updateVelocity(board);

	// Move In The Direction Of currentVelocity
	move();

	// Adjust tilePosition To Stay In Bounds
	adjustBounds(board);
}

/*
	Set targetTile
		Pacman's tilePosition
*/
void Blinky::calculateTargetTile(Pacman pacman) {
	if (mode == CHASE) {
		targetTile = pacman.getTilePosition();
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