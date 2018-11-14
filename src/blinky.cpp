#include "blinky.h"

// Constructors
Blinky::Blinky() {
	tilePosition = { 4, 1 };
}

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

	// Calculate pixelPosition
	calculatePixelPosition();
}

/*
	Set targetTile
		Pacman's tilePosition
*/
void Blinky::calculateTargetTile(Pacman pacman) {
	targetTile = pacman.getTilePosition();
}