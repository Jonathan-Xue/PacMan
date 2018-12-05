#include "blinky.h"

Blinky::Blinky() {}

Blinky::Blinky(vector<vector<Tile>> *b, Pacman *p) {
	ghostType = BLINKY;
	upAliveImage.load("images/sprites/blinky/up.png");
	leftAliveImage.load("images/sprites/blinky/left.png");
	downAliveImage.load("images/sprites/blinky/down.png");
	rightAliveImage.load("images/sprites/blinky/right.png");

	upDeadImage.load("images/sprites/dead/up.png");
	leftDeadImage.load("images/sprites/dead/left.png");
	downDeadImage.load("images/sprites/dead/down.png");
	rightDeadImage.load("images/sprites/dead/right.png");

	edibleImageOne.load("images/sprites/edible/blue.png");
	edibleImageTwo.load("images/sprites/edible/white.png");
	defaultColor = ofColor(255, 0, 0);

	board = b;
	pacman = p;
}

Blinky::~Blinky() {}

void Blinky::calculateTargetTile() {
	if (mode == CHASE) {
		targetTile = pacman->getTilePosition();
	}
	else if (mode == SCATTER) {
		targetTile = homeTilePosition;
	}
	else if (mode == FRIGHTENED) {
		// Do Nothing (targetTile Adjustment Is For Display Debugging Purposes)
		targetTile = vector<int>{ 0, 0 };
	}
	else {
		std::cerr << "Error. State Is Invalid" << std::endl;
		exit(1);
	}
}