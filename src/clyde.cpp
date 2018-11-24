#include "clyde.h"

Clyde::Clyde() {}

Clyde::~Clyde() {}

void Clyde::update(vector<vector<Tile>> board, Pacman pacman) {
	// Calculate targetTile
	calculateTargetTile(board, pacman);

	// Update currentVelocity
	updateVelocity(board);

	// Move In The Direction Of currentVelocity
	move();

	// Adjust tilePosition To Stay In Bounds
	adjustBounds(board);
}

void Clyde::calculateTargetTile(vector<vector<Tile>> board, Pacman pacman) {
	if (mode == CHASE) {
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
	else if (mode == SCATTER) {
		targetTile = homeTilePosition;
	}
	else if (mode == FRIGHTENED) {

	}
	else {
		std::cerr << "Error. GhostMode Is Invalid" << std::endl;
		exit(1);
	}
}