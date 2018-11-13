#include "pacman.h"

Pacman::Pacman() {
	tilePosition = { 23, 14 };
	pixelPosition = { (tilePosition[1] + currentTick[1] / 100) * 24, (tilePosition[0] + currentTick[0] / 100) * 24 };
	tilesPerSecond = 10;
	currentVelocity = { 0, 0 };
	queuedVelocity = { 0, 0 };
}

Pacman::~Pacman() {}

void Pacman::move(vector<vector<Tile>> &board) {
	// Calculate Tile Position
	calculatePixelPosition();

	// Ensure currentVelocity Is Valid
	if (!checkValidVelocity(board, currentVelocity)) {
		// Set currentVelocity
		if (currentTick[0] == 50.0 && currentTick[1] == 50.0) {
			currentVelocity = { 0, 0 };
		}
	}

	// Check To See If queuedVelocity Is Valid
	if (checkValidVelocity(board, queuedVelocity)) {
		// Recenter Pacman To Center Tick
		if (currentTick[0] == maxTick / 2 && currentTick[1] == maxTick / 2) {
			currentVelocity = queuedVelocity;
			queuedVelocity = { 0, 0 };
		}
	}

	// Eat Pellets
	board[tilePosition[0]][tilePosition[1]].setStandardPellet(false);
	board[tilePosition[0]][tilePosition[1]].setPowerPellet(false);

	// Adjust currentTick
	currentTick[1] += currentVelocity[0] * speed;
	currentTick[0] += currentVelocity[1] * speed;

	// Horizontal Movement
	if (std::abs(currentTick[1] - (maxTick / 2 - maxTick)) < 0.001) {
		currentTick[1] = 50;
		tilePosition[1]--;
	}
	else if (std::abs(currentTick[1] - (maxTick / 2 + maxTick)) < 0.001) {
		currentTick[1] = 50;
		tilePosition[1]++;
	}

	// Vertical Movement
	if (std::abs(currentTick[0] - (maxTick / 2 - maxTick)) < 0.001) {
		currentTick[0] = 50;
		tilePosition[0]--;
	}
	else if (std::abs(currentTick[0] - (maxTick / 2 + maxTick)) < 0.001) {
		currentTick[0] = 50;
		tilePosition[0]++;
	}
	std::cout << currentTick[1] << "\t" << currentTick[0] << std::endl;

	// Adjusts Bounds
	adjustBounds(board);
}

void Pacman::calculatePixelPosition() {
	pixelPosition[0] = (tilePosition[1] + (currentTick[1] / 100)) * tileSize;
	pixelPosition[1] = (tilePosition[0] + (currentTick[0] / 100)) * tileSize;
}

void Pacman::adjustBounds(vector<vector<Tile>> &board) {
	// Vertical OutOfBounds
	if (tilePosition[0] < 0) {
		tilePosition[0] = board.size() - 1;
	}
	else if (size_t(tilePosition[0]) >= board.size()) {
		tilePosition[0] = 0;
	}

	// Horizontal OutOfBounds
	if (tilePosition[1] < 0) {
		tilePosition[1] = board[0].size() - 1;
	}
	else if (size_t(tilePosition[1]) >= board[0].size()) {
		tilePosition[1] = 0;
	}

	calculatePixelPosition();
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

vector<double> Pacman::getPixelPosition() {
	return pixelPosition;
}

vector<int> Pacman::getTilePosition() {
	return tilePosition;
}

void Pacman::resize(int w, int h, int ts) {
	screenWidth = w;
	screenHeight = h;
	tileSize = ts;

	// maxTick * tilesPerSecond / FrameRate
	speed = maxTick * tilesPerSecond / 60;
}