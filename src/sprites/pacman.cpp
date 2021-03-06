#include "pacman.h"

Pacman::Pacman() {}

Pacman::Pacman(vector<vector<Tile>> *b) {
	board = b;
}

Pacman::~Pacman() {}

void Pacman::update() {
	if (skipFrames == vector<bool>{ false, false, false }) {
		// Eat Pellet
		eat();

		// Update currentVelocity
		updateVelocity();

		// Move In The Direction Of currentVelocity
		move();

		// Adjust tilePosition To Stay In Bounds
		adjustBounds();
	}
	else {
		for (unsigned i = 0; i < skipFrames.size(); i++) {
			if (skipFrames[i]) {
				skipFrames[i] = false;
				break;
			}
		}
	}
}

void Pacman::eat() {
	eatenPowerPellet = false;
	if ((*board)[tilePosition[0]][tilePosition[1]].isStandardPellet()) {
		score += 10;
		(*board)[tilePosition[0]][tilePosition[1]].setStandardPellet(false);

		// Flag
		skipFrames = vector<bool>{ true, false, false };
	}
	else if ((*board)[tilePosition[0]][tilePosition[1]].isPowerPellet()) {
		score += 50;
		(*board)[tilePosition[0]][tilePosition[1]].setPowerPellet(false);

		// Mode
		eatenPowerPellet = true;

		// Flag
		skipFrames = vector<bool>{ true, true, true };
	}
}

void Pacman::updateVelocity() {
	// Ensure currentVelocity Is Valid
	if (!checkValidVelocity(currentVelocity)) {
		// Set currentVelocity To { 0, 0 } If PacMan Is Within (Speed / 2) Ticks Of The Center Of The Tile
		if (abs(currentTick[0] - maxTick / 2) < (epsilon + speed / 2) && abs(currentTick[1] - maxTick / 2) < (epsilon + speed / 2)) {
			currentVelocity = { 0, 0 };
		}
	}

	// Check To See If queuedVelocity Is Valid
	if (checkValidVelocity(queuedVelocity)) {
		// Update currentVelocity To queuedVelocity If PacMan Is Within (Speed / 2) Ticks Of The Center Of The Tile
		if (abs(currentTick[0] - maxTick / 2) < (epsilon + speed / 2) && abs(currentTick[1] - maxTick / 2) < (epsilon + speed / 2)) {
			currentVelocity = queuedVelocity;
		}
	}
}

bool Pacman::checkValidVelocity(vector<int> velocity) {
	if (velocity == vector<int>{0, 0}) {
		return true;
	}
	else if (velocity == vector<int>{0, -1}) {
		// Up
		if (tilePosition[0] - 1 < 0 || (*board)[tilePosition[0] - 1][tilePosition[1]].getID() == 1) {
			return true;
		}
	}
	else if (velocity == vector<int>{-1, 0}) {
		// Left
		if (tilePosition[1] - 1 < 0 || (*board)[tilePosition[0]][tilePosition[1] - 1].getID() == 1) {
			return true;
		}
	}
	else if (velocity == vector<int>{0, 1}) {
		// Down
		if (unsigned(tilePosition[0] + 1) >= board->size() || (*board)[tilePosition[0] + 1][tilePosition[1]].getID() == 1) {
			return true;
		}
	}
	else if (velocity == vector<int>{1, 0}) {
		// Right
		if (unsigned(tilePosition[1] + 1) >= (*board)[0].size() || (*board)[tilePosition[0]][tilePosition[1] + 1].getID() == 1) {
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
	if (currentTick[1] < 0) {
		tilePosition[1]--;
		currentTick[1] = maxTick;
	}
	else if (currentTick[1] > maxTick) {
		tilePosition[1]++;
		currentTick[1] = 0.0;
	}

	// Vertical Movement & Tick Bounds
	if (currentTick[0] < 0) {
		tilePosition[0]--;
		currentTick[0] = maxTick;
	}
	else if (currentTick[0] > maxTick) {
		tilePosition[0]++;
		currentTick[0] = 0.0;
	}
}

void Pacman::adjustBounds() {
	// Vertical OutOfBounds
	if (tilePosition[0] < 0) {
		tilePosition[0] = board->size() - 1;
	}
	else if (tilePosition[0] >= (int)board->size()) {
		tilePosition[0] = 0;
	}

	// Horizontal OutOfBounds
	if (tilePosition[1] < 0) {
		tilePosition[1] = (*board)[0].size() - 1;
	}
	else if (tilePosition[1] >= (int)(*board)[0].size()) {
		tilePosition[1] = 0;
	}
}

void Pacman::resetLevel(int l) {
	level = l;

	mode = SCATTER;

	currentTilesPerSecond = defaultTilesPerSecond + level / 2;
	speed = maxTick * currentTilesPerSecond / frameRate;

	tilePosition = initialTilePosition;
	currentTick = vector<double>{ maxTick / 2, maxTick / 2 };

	currentVelocity = { 0, 0 };
	queuedVelocity = { -1, 0 };
}

void Pacman::resetGame() {
	level = 0;
	lives = maxLives;
	score = 0;

	mode = SCATTER;

	currentTilesPerSecond = defaultTilesPerSecond;
	speed = maxTick * currentTilesPerSecond / frameRate;

	tilePosition = initialTilePosition;
	currentTick = vector<double>{ maxTick / 2, maxTick / 2 };

	currentVelocity = { 0, 0 };
	queuedVelocity = { -1, 0 };
}

ofColor Pacman::getDefaultColor() {
	return defaultColor;
}

SpriteMode Pacman::getMode() {
	return mode;
}

int Pacman::getLives() {
	return lives;
}

int Pacman::getScore() {
	return score;
}

vector<double> Pacman::getCenterPixelPosition() {
	return vector<double>{ (tilePosition[1] + (currentTick[1] / maxTick)) * tileSize,
		(tilePosition[0] + (currentTick[0] / maxTick)) * tileSize };
}

vector<double> Pacman::getTopLeftPixelPosition() {
	return vector<double>{ (tilePosition[1] + (currentTick[1] / maxTick) - 0.5) * tileSize,
		(tilePosition[0] + (currentTick[0] / maxTick) - 0.5) * tileSize };
}

vector<int> Pacman::getTilePosition() {
	return tilePosition;
}

vector<int> Pacman::getInitialTilePosition() {
	return initialTilePosition;
}

vector<int> Pacman::getCurrentVelocity() {
	return currentVelocity;
}

bool Pacman::hasEatenPowerPellet() {
	return eatenPowerPellet;
}

void Pacman::setMode(SpriteMode m) {
	mode = m;
}

void Pacman::decrementLives() {
	lives--;
}

void Pacman::incrementScore(int s) {
	score += s;
}

void Pacman::setInitialTilePosition(vector<int> itp) {
	initialTilePosition = itp;
	tilePosition = itp;
}

void Pacman::setQueuedVelocity(vector<int> v) {
	queuedVelocity = v;
}

void Pacman::resize(int w, int h, int ts) {
	screenWidth = w;
	screenHeight = h;
	tileSize = ts;

	speed = maxTick * currentTilesPerSecond / frameRate;
}