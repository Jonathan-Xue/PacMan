#include "pinky.h"

Pinky::Pinky() {}

Pinky::Pinky(vector<vector<Tile>> *b, Pacman *p) {
	ghostType = PINKY;
	upAliveImage.load("images/sprites/pinky/up.png");
	leftAliveImage.load("images/sprites/pinky/left.png");
	downAliveImage.load("images/sprites/pinky/down.png");
	rightAliveImage.load("images/sprites/pinky/right.png");

	upDeadImage.load("images/sprites/dead/up.png");
	leftDeadImage.load("images/sprites/dead/left.png");
	downDeadImage.load("images/sprites/dead/down.png");
	rightDeadImage.load("images/sprites/dead/right.png");

	edibleImageOne.load("images/sprites/edible/blue.png");
	edibleImageTwo.load("images/sprites/edible/white.png");
	defaultColor = ofColor(255, 185, 255);

	board = b;
	pacman = p;
}

Pinky::~Pinky() {}

void Pinky::calculateTargetTile() {
	if (mode == CHASE) {
		// Pacman's Velocity Vector
		vector<int> pacmanVelocity = pacman->getCurrentVelocity();

		if (pacmanVelocity == vector<int>{0, 0}) {
			// Nothing
			targetTilePosition = targetTilePosition;
		}
		else if (pacmanVelocity == vector<int>{0, -1}) {
			// Up
			targetTilePosition[0] = pacman->getTilePosition()[0] - 4;
			targetTilePosition[1] = pacman->getTilePosition()[1];
		}
		else if (pacmanVelocity == vector<int>{-1, 0}) {
			// Left
			targetTilePosition[0] = pacman->getTilePosition()[0];
			targetTilePosition[1] = pacman->getTilePosition()[1] - 4;
		}
		else if (pacmanVelocity == vector<int>{0, 1}) {
			// Down
			targetTilePosition[0] = pacman->getTilePosition()[0] + 4;
			targetTilePosition[1] = pacman->getTilePosition()[1];
		}
		else if (pacmanVelocity == vector<int>{1, 0}) {
			// Right
			targetTilePosition[0] = pacman->getTilePosition()[0];
			targetTilePosition[1] = pacman->getTilePosition()[1] + 4;
		}
		else {
			std::cerr << "Error. Pacman's Velocity Vector Is Invalid" << std::endl;
			std::exit(1);
		}
	}
	else if (mode == SCATTER) {
		targetTilePosition = homeTilePosition;
	}
	else if (mode == FRIGHTENED) {
		// Do Nothing (targetTile Adjustment Is For Display Debugging Purposes)
		targetTilePosition = vector<int>{ 0, 0 };
	}
	else {
		std::cerr << "Error. State Is Invalid" << std::endl;
		exit(1);
	}
}