#include "pacman.h"

Pacman::Pacman() {
	tilePosition = { 14, 23 };
	pixelPosition = { tilePosition[0] * 24 + 12, tilePosition[1] * 24 + 12 };
	tilesPerSecond = 5;
	currentVelocity = { 0, 0 };
	queuedVelocity = { 0, 0 };
}

Pacman::~Pacman() {}

void Pacman::calculateTilePosition() {
	tilePosition[0] = pixelPosition[1] / tileSize;
	tilePosition[1] = pixelPosition[0] / tileSize;
}

void Pacman::move(vector<vector<Tile>> &board) {
	// Calculate Tile Position
	calculateTilePosition();

	// Vertical OutOfBounds
	if (tilePosition[0] < 0) {
		tilePosition[0] = board.size() - 1;
		pixelPosition[1] = tilePosition[0] * tileSize + tileSize;
	}
	else if (tilePosition[0] >= board.size()) {
		tilePosition[0] = 0;
		pixelPosition[1] = tilePosition[0] * tileSize;
	}

	// Horizontal OutOfBounds
	if (tilePosition[1] < 0) {
		tilePosition[1] = board[0].size() - 1;
		pixelPosition[0] = tilePosition[1] * tileSize + tileSize;
	}
	else if (tilePosition[1] >= board[0].size()) {
		tilePosition[1] = 0;
		pixelPosition[0] = tilePosition[1] * tileSize;
	}

	// Ensure currentVelocity Is Valid
	if (!checkValidVelocity(board, currentVelocity)) {
		// Recenter Pacman To Tile Center
		pixelPosition[0] = tilePosition[1] * tileSize + tileSize / 2;
		pixelPosition[1] = tilePosition[0] * tileSize + tileSize / 2;

		// Set currentVelocity
		currentVelocity = { 0, 0 };
	}

	// Check To See If queuedVelocity Is Valid
	if (checkValidVelocity(board, queuedVelocity)) {
		// Recenter Pacman To Tile Center
		if (queuedVelocity[1] == -1 || queuedVelocity[1] == 1) {
			pixelPosition[0] = tilePosition[1] * tileSize + tileSize / 2;
		}
		else {
			pixelPosition[1] = tilePosition[0] * tileSize + tileSize / 2;
		}

		// Set currentVelocity
		currentVelocity = queuedVelocity;
		queuedVelocity = { 0, 0 };
	}

	// Eat Pellets
	board[tilePosition[0]][tilePosition[1]].setStandardPellet(false);
	board[tilePosition[0]][tilePosition[1]].setPowerPellet(false);

	// Adjust pixelPosition
	pixelPosition[0] += currentVelocity[0] * speed;
	pixelPosition[1] += currentVelocity[1] * speed;
	
}

bool Pacman::checkValidVelocity(vector<vector<Tile>> &board, vector<int> velocity) {
	if (velocity[0] == 0 && velocity[1] == 0) {
		return false;
	}
	else if (velocity[0] == 0 && velocity[1] == -1) {
		// Up
		if (tilePosition[0] - 1 < 0 || board[tilePosition[0] - 1][tilePosition[1]].getID() == 1) {
			return true;
		}
	}
	else if (velocity[0] == -1 && velocity[1] == 0) {
		// Left
		if (tilePosition[1] - 1 < 0 || board[tilePosition[0]][tilePosition[1] - 1].getID() == 1) {
			return true;
		}
	}
	else if (velocity[0] == 0 && velocity[1] == 1) {
		// Down
		if (size_t(tilePosition[0] + 1) >= board.size() || board[tilePosition[0] + 1][tilePosition[1]].getID() == 1) {
			return true;
		}
	}
	else if (velocity[0] == 1 && velocity[1] == 0) {
		// Right
		if (size_t(tilePosition[1] + 1) >= board[0].size() || board[tilePosition[0]][tilePosition[1] + 1].getID() == 1) {
			return true;
		}
	}
	else {
		std::cerr << "Error. Velocity Vector Is Invalid" << std::endl;
		std::exit(1);
	}

	return false;
}

void Pacman::setQueuedVelocity(vector<int> v) {
	queuedVelocity = v;
}

vector<int> Pacman::getPixelPosition() {
	return pixelPosition;
}

vector<int> Pacman::getTilePosition() {
	return tilePosition;
}

void Pacman::resize(int w, int h, int ts) {
	screenWidth = w;
	screenHeight = h;
	tileSize = ts;

	// tileSize * tilesPerSecond / FrameRate
	speed = tileSize * tilesPerSecond / 60;
}