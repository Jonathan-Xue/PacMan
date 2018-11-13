#include "Ghost.h"

// Constructors
Ghost::Ghost() {
	tilePosition = { 0, 0 };
}

Ghost::~Ghost() {}

// Methods
void Ghost::update(vector<vector<Tile>> &board) {
	// Update currentVelocity
	updateVelocity(board);

	// Move In The Direction Of currentVelocity
	move();

	// Adjust tilePosition To Stay In Bounds
	adjustBounds(board);

	// Calculate pixelPosition
	calculatePixelPosition();
}

void Ghost::updateVelocity(vector<vector<Tile>> board) {
	// Check To See If queuedVelocity Is Valid
	vector<vector<int>> allVelocities{ {0, -1}, {-1, 0}, {0, 1}, {1, 0} };

	for (int i = 0; i < 1000000000; i++) {
		queuedVelocity = allVelocities[rand() % 4];
		if (checkValidVelocity(board, queuedVelocity)) {
			// Update currentVelocity To queuedVelocity If Ghost Is In The Center Of The Tile
			if (abs(currentTick[0] - maxTick / 2) < epsilon && abs(currentTick[1] - maxTick / 2) < epsilon) {
				currentVelocity = queuedVelocity;
				queuedVelocity = { 0, 0 };
			}

			break;
		}
	}
}

bool Ghost::checkValidVelocity(vector<vector<Tile>> board, vector<int> velocity) {
	if (velocity == vector<int>{0, 0}) {
		return false;
	}
	else if (velocity == vector<int>{0, -1}) {
		// Up
		if (currentVelocity != vector<int>{0, 1} && 
			(tilePosition[0] - 1 < 0 || board[tilePosition[0] - 1][tilePosition[1]].getID() == 1)) {
			return true;
		}
	}
	else if (velocity == vector<int>{-1, 0}) {
		// Left
		if (currentVelocity != vector<int>{1, 0} && 
			(tilePosition[1] - 1 < 0 || board[tilePosition[0]][tilePosition[1] - 1].getID() == 1)) {
			return true;
		}
	}
	else if (velocity == vector<int>{0, 1}) {
		// Down
		if (currentVelocity != vector<int>{0, -1} && 
			(size_t(tilePosition[0] + 1) >= board.size() || board[tilePosition[0] + 1][tilePosition[1]].getID() == 1)) {
			return true;
		}
	}
	else if (velocity == vector<int>{1, 0}) {
		// Right
		if (currentVelocity != vector<int>{-1, 0} &&
			(size_t(tilePosition[1] + 1) >= board[0].size() || board[tilePosition[0]][tilePosition[1] + 1].getID() == 1)) {
			return true;
		}
	}
	else {
		std::cerr << "Error. Velocity Vector Is Invalid" << std::endl;
		std::exit(1);
	}

	return false;
}

void Ghost::move() {
	// Adjust currentTick
	currentTick[1] += currentVelocity[0] * speed;
	currentTick[0] += currentVelocity[1] * speed;

	// Horizontal Movement & Tick Bounds
	if (std::abs(currentTick[1]) < epsilon) {
		tilePosition[1]--;
		currentTick[1] = maxTick;
	}
	else if (std::abs(currentTick[1] - maxTick) < epsilon) {
		tilePosition[1]++;
		currentTick[1] = 0.0;
	}

	// Vertical Movement & Tick Bounds
	if (std::abs(currentTick[0]) < epsilon) {
		tilePosition[0]--;
		currentTick[0] = maxTick;
	}
	else if (std::abs(currentTick[0] - maxTick) < epsilon) {
		tilePosition[0]++;
		currentTick[0] = 0.0;
	}
}

void Ghost::adjustBounds(vector<vector<Tile>> board) {
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
}

void Ghost::calculatePixelPosition() {
	pixelPosition[0] = (tilePosition[1] + (currentTick[1] / 100)) * tileSize;
	pixelPosition[1] = (tilePosition[0] + (currentTick[0] / 100)) * tileSize;
}

// Getters
vector<double> Ghost::getPixelPosition() {
	return pixelPosition;
}

vector<int> Ghost::getTilePosition() {
	return tilePosition;
}

void Ghost::resize(int w, int h, int ts) {
	screenWidth = w;
	screenHeight = h;
	tileSize = ts;

	speed = maxTick * tilesPerSecond / 60;
}