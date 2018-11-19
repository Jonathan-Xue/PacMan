#include "pacman.h"

// Constructors
Pacman::Pacman() {}

Pacman::~Pacman() {}

// Methods
void Pacman::update(vector<vector<Tile>> &board) {
	// Eat Pellet
	eat(board);

	// Update currentVelocity
	updateVelocity(board);

	// Move In The Direction Of currentVelocity
	move();

	// Adjust tilePosition To Stay In Bounds
	adjustBounds(board);

	// Calculate pixelPosition
	calculatePixelPosition();
}

void Pacman::eat(vector<vector<Tile>> &board) {
	board[tilePosition[0]][tilePosition[1]].setStandardPellet(false);
	board[tilePosition[0]][tilePosition[1]].setPowerPellet(false);
}

void Pacman::updateVelocity(vector<vector<Tile>> board) {
	// Ensure currentVelocity Is Valid
	if (!checkValidVelocity(board, currentVelocity)) {
		// Set currentVelocity To { 0, 0 } If PacMan Is Within (Speed / 2) Ticks Of The Center Of The Tile
		if (abs(currentTick[0] - maxTick / 2) < (epsilon + speed / 2) && abs(currentTick[1] - maxTick / 2) < (epsilon + speed / 2)) {
			currentVelocity = { 0, 0 };
		}
	}

	// Check To See If queuedVelocity Is Valid
	if (checkValidVelocity(board, queuedVelocity)) {
		// Update currentVelocity To queuedVelocity If PacMan Is Within (Speed / 2) Ticks Of The Center Of The Tile
		if (abs(currentTick[0] - maxTick / 2) < (epsilon + speed / 2) && abs(currentTick[1] - maxTick / 2) < (epsilon + speed / 2)) {
			currentVelocity = queuedVelocity;
			queuedVelocity = { 0, 0 };
		}
	}
}

bool Pacman::checkValidVelocity(vector<vector<Tile>> board, vector<int> velocity) {
	if (velocity == vector<int>{0, 0}) {
		return false;
	}
	else if (velocity == vector<int>{0, -1}) {
		// Up
		if (tilePosition[0] - 1 < 0 || board[tilePosition[0] - 1][tilePosition[1]].getID() == 1) {
			return true;
		}
	}
	else if (velocity == vector<int>{-1, 0}) {
		// Left
		if (tilePosition[1] - 1 < 0 || board[tilePosition[0]][tilePosition[1] - 1].getID() == 1) {
			return true;
		}
	}
	else if (velocity == vector<int>{0, 1}) {
		// Down
		if (size_t(tilePosition[0] + 1) >= board.size() || board[tilePosition[0] + 1][tilePosition[1]].getID() == 1) {
			return true;
		}
	}
	else if (velocity == vector<int>{1, 0}) {
		// Right
		if (size_t(tilePosition[1] + 1) >= board[0].size() || board[tilePosition[0]][tilePosition[1] + 1].getID() == 1) {
			return true;
		}
	}
	else {
		// Exit With Error Message
		std::cerr << "Error. Pacman Velocity Vector Is Invalid" << std::endl;
		std::exit(1);
	}

	return false;
}

void Pacman::move() {
	// Adjust currentTick
	currentTick[1] += currentVelocity[0] * speed;
	currentTick[0] += currentVelocity[1] * speed;

	// Horizontal Movement & Tick Bounds
	if (std::abs(currentTick[1]) < (epsilon + speed / 2)) {
		tilePosition[1]--;
		currentTick[1] = maxTick;
	}
	else if (std::abs(currentTick[1] - maxTick) < (epsilon + speed / 2)) {
		tilePosition[1]++;
		currentTick[1] = 0.0;
	}

	// Vertical Movement & Tick Bounds
	if (std::abs(currentTick[0]) < (epsilon + speed / 2)) {
		tilePosition[0]--;
		currentTick[0] = maxTick;
	}
	else if (std::abs(currentTick[0] - maxTick) < (epsilon + speed / 2)) {
		tilePosition[0]++;
		currentTick[0] = 0.0;
	}
}

void Pacman::adjustBounds(vector<vector<Tile>> board) {
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

void Pacman::calculatePixelPosition() {
	pixelPosition[0] = (tilePosition[1] + (currentTick[1] / maxTick)) * tileSize;
	pixelPosition[1] = (tilePosition[0] + (currentTick[0] / maxTick)) * tileSize;
}

// Reset Functions
void Pacman::resetLevel(int l) {
	level = l;
	lives--;

	tilePosition = initialTilePosition;
}

void Pacman::resetGame() {
	level = 0;
	lives = 3;
	score = 0;

	tilePosition = initialTilePosition;
}

// Getters
int Pacman::getLives() {
	return lives;
}

vector<double> Pacman::getPixelPosition() {
	return pixelPosition;
}

vector<int> Pacman::getTilePosition() {
	return tilePosition;
}

vector<int> Pacman::getCurrentVelocity() {
	return currentVelocity;
}

// Setters
void Pacman::setInitialPosition(vector<int> itp) {
	initialTilePosition = itp;
	tilePosition = itp;
}

void Pacman::setQueuedVelocity(vector<int> v) {
	queuedVelocity = v;
}

// Resize
void Pacman::resize(int w, int h, int ts) {
	screenWidth = w;
	screenHeight = h;
	tileSize = ts;

	speed = maxTick * tilesPerSecond / frameRate;
}