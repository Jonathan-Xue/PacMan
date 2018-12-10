#include "clyde.h"

Clyde::Clyde() {}

Clyde::Clyde(vector<vector<Tile>> *b, Pacman *p) {
	ghostType = CLYDE;
	upAliveImage.load("images/sprites/clyde/up.png");
	leftAliveImage.load("images/sprites/clyde/left.png");
	downAliveImage.load("images/sprites/clyde/down.png");
	rightAliveImage.load("images/sprites/clyde/right.png");

	upDeadImage.load("images/sprites/dead/up.png");
	leftDeadImage.load("images/sprites/dead/left.png");
	downDeadImage.load("images/sprites/dead/down.png");
	rightDeadImage.load("images/sprites/dead/right.png");

	edibleImageOne.load("images/sprites/edible/blue.png");
	edibleImageTwo.load("images/sprites/edible/white.png");
	defaultColor = ofColor(255, 185, 80);

	board = b;
	pacman = p;
}

Clyde::~Clyde() {}

void Clyde::calculateTargetTile() {
	if (mode == CHASE) {
		double distance = calculateDistance(tileSize * (pacman->getTilePosition()[0] + 0.5),
			tileSize * (pacman->getTilePosition()[1] + 0.5),
			tileSize * (tilePosition[0] + (currentTick[0] / maxTick)),
			tileSize * (tilePosition[1] + (currentTick[1] / maxTick)));

		if (distance < 8.0 * tileSize) {
			targetTilePosition = { (int)(board->size() - 1), 0 };
		}
		else {
			targetTilePosition = pacman->getTilePosition();
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
		std::cerr << "Error. GhostMode Is Invalid" << std::endl;
		exit(1);
	}
}