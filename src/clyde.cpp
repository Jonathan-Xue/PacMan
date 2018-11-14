#include "clyde.h"

// Constructors
Clyde::Clyde() {
	tilePosition = {32, 26};
}

Clyde::~Clyde() {}

// Methods
void Clyde::update(vector<vector<Tile>> board, Pacman pacman) {
	// Calculate targetTile
	calculateTargetTile(board, pacman);

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
		Within 8 Units Of Pacman
			Bottom Left Corner
		Else
			Pacman's tilePosition
*/
void Clyde::calculateTargetTile(vector<vector<Tile>> board, Pacman pacman) {
	double distance = calculateDistance(tileSize * (pacman.getTilePosition()[0] + 0.5),
										tileSize * (pacman.getTilePosition()[1] + 0.5),
										tileSize * (tilePosition[0] + (currentTick[0] / maxTick)),
										tileSize * (tilePosition[1] + (currentTick[1] / maxTick)));

	if (distance < 8.0 * tileSize) {
		targetTile = { (int)(board.size() - 1), 0 };
	}
	else {
		targetTile = pacman.getTilePosition();
	}
}