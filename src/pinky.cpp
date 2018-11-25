#include "pinky.h"

Pinky::Pinky() {}

Pinky::Pinky(vector<vector<Tile>> *b, Pacman *p) {
	board = b;
	pacman = p;
}

Pinky::~Pinky() {}

void Pinky::update() {
	// Calculate targetTile
	calculateTargetTile();

	// Update currentVelocity
	updateVelocity();

	// Move In The Direction Of currentVelocity
	move();

	// Adjust tilePosition To Stay In Bounds
	adjustBounds();
}

void Pinky::calculateTargetTile() {
	if (mode == CHASE) {
		// Pacman's Velocity Vector
		vector<int> pacmanVelocity = (*pacman).getCurrentVelocity();

		if (pacmanVelocity == vector<int>{0, 0}) {
			// Nothing
			targetTile = targetTile;
		}
		else if (pacmanVelocity == vector<int>{0, -1}) {
			// Up
			targetTile[0] = (*pacman).getTilePosition()[0] - 4;
			targetTile[1] = (*pacman).getTilePosition()[1] - 4;
		}
		else if (pacmanVelocity == vector<int>{-1, 0}) {
			// Left
			targetTile[0] = (*pacman).getTilePosition()[0];
			targetTile[1] = (*pacman).getTilePosition()[1] - 4;
		}
		else if (pacmanVelocity == vector<int>{0, 1}) {
			// Down
			targetTile[0] = (*pacman).getTilePosition()[0] + 4;
			targetTile[1] = (*pacman).getTilePosition()[1];
		}
		else if (pacmanVelocity == vector<int>{1, 0}) {
			// Right
			targetTile[0] = (*pacman).getTilePosition()[0];
			targetTile[1] = (*pacman).getTilePosition()[1] + 4;
		}
		else {
			std::cerr << "Error. Pacman's Velocity Vector Is Invalid" << std::endl;
			std::exit(1);
		}
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