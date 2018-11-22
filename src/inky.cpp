#include "inky.h"

// Constructors
Inky::Inky() {}

Inky::~Inky() {}

// Methods
void Inky::update(vector<vector<Tile>> board, Pacman pacman, Blinky blinky) {
	// Calculate targetTile
	calculateTargetTile(pacman, blinky);

	// Update currentVelocity
	updateVelocity(board);

	// Move In The Direction Of currentVelocity
	move();

	// Adjust tilePosition To Stay In Bounds
	adjustBounds(board);
}

/*
	Set targetTile
		Pacman Moving Up:
			Two Tiles Up And Two Tiles Left Of Pacman's Current Position
		Pacman Moving Left
			Two Tiles Left Of Pacman's Current Position
		Pacman Moving Down
			Two Tiles Down Of Pacman's Current Position
		Pacman Moving Right
			Two Tiles Right Of Pacman's Current Position

		Double the Corresponding Vector From Blinky To ^^^
*/
void Inky::calculateTargetTile(Pacman pacman, Blinky blinky) {
	if (state == CHASE) {
		// Static Variable To Retain Two Tiles Calculation For When Pacman's Velocity = { 0, 0 }
		static vector<int> tempTile = { 0, 0 };

		// Two Tiles Calculation
		vector<int> pacmanVelocity = pacman.getCurrentVelocity();

		if (pacmanVelocity == vector<int>{0, 0}) {
			// Nothing
			tempTile = tempTile;
		}
		else if (pacmanVelocity == vector<int>{0, -1}) {
			// Up
			tempTile[0] = pacman.getTilePosition()[0] - 2;
			tempTile[1] = pacman.getTilePosition()[1] - 2;
		}
		else if (pacmanVelocity == vector<int>{-1, 0}) {
			// Left
			tempTile[0] = pacman.getTilePosition()[0];
			tempTile[1] = pacman.getTilePosition()[1] - 2;
		}
		else if (pacmanVelocity == vector<int>{0, 1}) {
			// Down
			tempTile[0] = pacman.getTilePosition()[0] + 2;
			tempTile[1] = pacman.getTilePosition()[1];
		}
		else if (pacmanVelocity == vector<int>{1, 0}) {
			// Right
			tempTile[0] = pacman.getTilePosition()[0];
			tempTile[1] = pacman.getTilePosition()[1] + 2;
		}
		else {
			std::cerr << "Error. Pacman Velocity Vector Is Invalid" << std::endl;
			std::exit(1);
		}

		// Double The Vector From Blinky To The targetTile
		targetTile[0] = tempTile[0] + (tempTile[0] - blinky.getTilePosition()[0]);
		targetTile[1] = tempTile[1] + (tempTile[1] - blinky.getTilePosition()[1]);
	}
	else if (state == SCATTER) {
		targetTile = homeTilePosition;
	}
	else if (state == FRIGHTENED) {

	}
	else {
		std::cerr << "Error. State Is Invalid" << std::endl;
		exit(1);
	}
}