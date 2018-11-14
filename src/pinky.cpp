#include "pinky.h"

// Constructors
Pinky::Pinky() {
	tilePosition = { 4, 26 };
}

Pinky::~Pinky() {}

// Methods
void Pinky::update(vector<vector<Tile>> board, Pacman pacman) {
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
		Pacman Moving Up:
			Four Tiles Up And Four Tiles Left Of Pacman's Current Position
		Pacman Moving Left
			Four Tiles Left Of Pacman's Current Position
		Pacman Moving Down
			Four Tiles Down Of Pacman's Current Position
		Pacman Moving Right
			Four Tiles Right Of Pacman's Current Position
*/	
void Pinky::calculateTargetTile(Pacman pacman) {
	vector<int> pacmanVelocity = pacman.getCurrentVelocity();

	if (pacmanVelocity == vector<int>{0, 0}) {
		// Nothing
		targetTile = targetTile;
	}
	else if (pacmanVelocity == vector<int>{0, -1}) {
		// Up
		targetTile[0] = pacman.getTilePosition()[0] - 4;
		targetTile[1] = pacman.getTilePosition()[1] - 4;
	}
	else if (pacmanVelocity == vector<int>{-1, 0}) {
		// Left
		targetTile[0] = pacman.getTilePosition()[0];
		targetTile[1] = pacman.getTilePosition()[1] - 4;
	}
	else if (pacmanVelocity == vector<int>{0, 1}) {
		// Down
		targetTile[0] = pacman.getTilePosition()[0] + 4;
		targetTile[1] = pacman.getTilePosition()[1];
	}
	else if (pacmanVelocity == vector<int>{1, 0}) {
		// Right
		targetTile[0] = pacman.getTilePosition()[0];
		targetTile[1] = pacman.getTilePosition()[1] + 4;
	}
	else {
		std::cerr << "Error. Pacman Velocity Vector Is Invalid" << std::endl;
		std::exit(1);
	}
}