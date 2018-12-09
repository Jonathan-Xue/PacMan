#include "Ghost.h"

Ghost::Ghost() {}

Ghost::~Ghost() {}

void Ghost::update() {
	// Calculate targetTile
	if (alive) {
		calculateTargetTile();
	}
	else {
		targetTilePosition = initialTilePosition;
	}

	// Update currentVelocity
	updateVelocity();

	// Move In The Direction Of currentVelocity
	move();

	// Adjust tilePosition To Stay In Bounds
	adjustBounds();

	// Check To See If Ghost Should Be Alive
	if (!alive && tilePosition == targetTilePosition) {
		alive = true;
		edible = false;
	}
}

void Ghost::calculateTargetTile() {}

void Ghost::updateVelocity() {
	if (reverseDirectionFlag) {
		// Reverse Direction Of Travel
		currentVelocity[0] *= -1;
		currentVelocity[1] *= -1;

		reverseDirectionFlag = false;
	}
	else if (mode == FRIGHTENED && alive) {
		// Update currentVelocity To queuedVelocity If Ghost Is Within (Speed / 2) Ticks Of The Center Of The Tile
		if (abs(currentTick[0] - maxTick / 2) < (epsilon + speed / 2) && abs(currentTick[1] - maxTick / 2) < (epsilon + speed / 2)) {
			int randIndex = rand() % queuedVelocity.size();
			if (checkValidVelocity(queuedVelocity[randIndex])) {
				// Tries To Move In A Random Velocity
				currentVelocity = queuedVelocity[randIndex];
			}
			else {
				// Retrieve Valid Velocities From queuedVelocity And Append It To possibleVelocity
				vector<vector<int>> possibleVelocity{};

				for (int i = 0; i < 4; i++) {
					if (checkValidVelocity(queuedVelocity[i])) {
						possibleVelocity.push_back(queuedVelocity[i]);
					}
				}

				// Update currentVelocity
				currentVelocity = possibleVelocity[0];
			}
		}

	}
	else {
		// Update currentVelocity To queuedVelocity If Ghost Is Within (Speed / 2) Ticks Of The Center Of The Tile
		if (abs(currentTick[0] - maxTick / 2) < (epsilon + speed / 2) && abs(currentTick[1] - maxTick / 2) < (epsilon + speed / 2)) {
			// Center The Ghost In The Tile
			// currentTick = vector<double>{ maxTick / 2, maxTick / 2 };

			// Retrieve Valid Velocities From queuedVelocity And Append It To possibleVelocity
			vector<vector<int>> possibleVelocity{};

			for (int i = 0; i < 4; i++) {
				if (checkValidVelocity(queuedVelocity[i])) {
					possibleVelocity.push_back(queuedVelocity[i]);
				}
			}

			// Determine The Velocity Which Yields In Closest Distance To targetTile
			int minIndex = -1;
			double minVal = 1000000000.0;

			for (unsigned i = 0; i < possibleVelocity.size(); i++) {
				double distance = calculateDistance(tileSize * (targetTilePosition[0] + 0.5),
					tileSize * (targetTilePosition[1] + 0.5),
					tileSize * (tilePosition[0] + (currentTick[0] / maxTick) + possibleVelocity[i][1]),
					tileSize * (tilePosition[1] + (currentTick[1] / maxTick) + possibleVelocity[i][0]));

				if (distance < minVal) {
					minIndex = i;
					minVal = distance;
				}
			}

			// Update currentVelocity
			currentVelocity = possibleVelocity[minIndex];
		}
	}
}

bool Ghost::checkValidVelocity(vector<int> velocity) {
	if (velocity == vector<int>{0, 0}) {
		return true;
	}
	else if (velocity == vector<int>{0, -1}) {
		// Up
		if (currentVelocity != vector<int>{0, 1} &&
			(tilePosition[0] - 1 < 0 || (*board)[tilePosition[0] - 1][tilePosition[1]].getID() == 1)) {
			return true;
		}
	}
	else if (velocity == vector<int>{-1, 0}) {
		// Left
		if (currentVelocity != vector<int>{1, 0} &&
			(tilePosition[1] - 1 < 0 || (*board)[tilePosition[0]][tilePosition[1] - 1].getID() == 1)) {
			return true;
		}
	}
	else if (velocity == vector<int>{0, 1}) {
		// Down
		if (currentVelocity != vector<int>{0, -1} &&
			(unsigned(tilePosition[0] + 1) >= board->size() || (*board)[tilePosition[0] + 1][tilePosition[1]].getID() == 1)) {
			return true;
		}
	}
	else if (velocity == vector<int>{1, 0}) {
		// Right
		if (currentVelocity != vector<int>{-1, 0} &&
			(unsigned(tilePosition[1] + 1) >= (*board)[0].size() || (*board)[tilePosition[0]][tilePosition[1] + 1].getID() == 1)) {
			return true;
		}
	}
	else {
		std::cerr << "Error. Velocity Vector Is Invalid" << std::endl;
		std::exit(1);
	}

	return false;
}

double Ghost::calculateDistance(double x1, double y1, double x2, double y2) {
	double dx = x2 - x1;
	double dy = y2 - y1;

	return sqrt(pow(dx, 2) + pow(dy, 2));
}

void Ghost::move() {
	// Adjust currentTick
	currentTick[1] += currentVelocity[0] * speed;
	currentTick[0] += currentVelocity[1] * speed;

	// Horizontal Movement & Tick Bounds
	if (currentTick[1] < 0) {
		tilePosition[1]--;
		currentTick[1] = maxTick;

		// reverseDirectionFlag
		if (queuedReverseDirectionFlag) {
			reverseDirectionFlag = true;
			queuedReverseDirectionFlag = false;
		}
	}
	else if (currentTick[1] > maxTick) {
		tilePosition[1]++;
		currentTick[1] = 0.0;

		// reverseDirectionFlag
		if (queuedReverseDirectionFlag) {
			reverseDirectionFlag = true;
			queuedReverseDirectionFlag = false;
		}
	}

	// Vertical Movement & Tick Bounds
	if (currentTick[0] < 0) {
		tilePosition[0]--;
		currentTick[0] = maxTick;

		// reverseDirectionFlag
		if (queuedReverseDirectionFlag) {
			reverseDirectionFlag = true;
			queuedReverseDirectionFlag = false;
		}
	}
	else if (currentTick[0] > maxTick) {
		tilePosition[0]++;
		currentTick[0] = 0.0;

		// reverseDirectionFlag
		if (queuedReverseDirectionFlag) {
			reverseDirectionFlag = true;
			queuedReverseDirectionFlag = false;
		}
	}
}

void Ghost::adjustBounds() {
	// Vertical OutOfBounds
	if (tilePosition[0] < 0) {
		tilePosition[0] = board->size() -  1;
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

void Ghost::resetLevel(int l) {
	alive = true;
	edible = false;
	level = l;

	mode = SCATTER;

	tilePosition = initialTilePosition;
	currentTick = vector<double>{ maxTick / 2, maxTick / 2 };

	currentVelocity = { 0, 0 };
}

void Ghost::resetGame() {
	alive = true;
	edible = false;
	level = 0;

	mode = SCATTER;

	tilePosition = initialTilePosition;
	currentTick = vector<double>{ maxTick / 2, maxTick / 2 };

	currentVelocity = { 0, 0 };
}

void Ghost::resize(int w, int h, int ts) {
	screenWidth = w;
	screenHeight = h;
	tileSize = ts;

	speed = maxTick * tilesPerSecond / frameRate;
}

GhostType Ghost::getGhostType() {
	return ghostType;
}

ofImage Ghost::getImage() {
	if (alive) {
		if (edible) {
			if (whichEdibleImage) {
				return edibleImageOne;
			}
			else {
				return edibleImageTwo;
			}
		}
		else {
			if (currentVelocity == vector<int>{0, 0}) {
				// Up
				return downAliveImage;
			}
			else if (currentVelocity == vector<int>{0, -1}) {
				// Up
				return upAliveImage;
			}
			else if (currentVelocity == vector<int>{-1, 0}) {
				// Left
				return leftAliveImage;
			}
			else if (currentVelocity == vector<int>{0, 1}) {
				// Down
				return downAliveImage;
			}
			else if (currentVelocity == vector<int>{1, 0}) {
				// Right
				return rightAliveImage;
			}
		}
	}
	else {
		if (currentVelocity == vector<int>{0, 0}) {
			// Up
			return downDeadImage;
		}
		else if (currentVelocity == vector<int>{0, -1}) {
			// Up
			return upDeadImage;
		}
		else if (currentVelocity == vector<int>{-1, 0}) {
			// Left
			return leftDeadImage;
		}
		else if (currentVelocity == vector<int>{0, 1}) {
			// Down
			return downDeadImage;
		}
		else if (currentVelocity == vector<int>{1, 0}) {
			// Right
			return rightDeadImage;
		}
	}
	
	return ofImage();
}

ofColor Ghost::getDefaultColor() {
	return defaultColor;
}

bool Ghost::isAlive() {
	return alive;
}

bool Ghost::isEdible() {
	return edible;
}

SpriteMode Ghost::getMode() {
	return mode;
}

vector<double> Ghost::getCenterPixelPosition() {
	return vector<double>{ (tilePosition[1] + (currentTick[1] / maxTick)) * tileSize,
		(tilePosition[0] + (currentTick[0] / maxTick)) * tileSize };
}

vector<double> Ghost::getTopLeftPixelPosition() {
	return vector<double>{ (tilePosition[1] + (currentTick[1] / maxTick) - 0.5) * tileSize,
		(tilePosition[0] + (currentTick[0] / maxTick) - 0.5) * tileSize };
}

vector<int> Ghost::getTilePosition() {
	return tilePosition;
}

vector<int> Ghost::getInitialTilePosition() {
	return initialTilePosition;
}

vector<int> Ghost::getHomeTilePosition() {
	return homeTilePosition;
}

vector<double> Ghost::getTargetTilePixelPosition() {
	return vector<double>{ (targetTilePosition[1] + 0.5) * tileSize, (targetTilePosition[0] + 0.5) * tileSize };
}

vector<int> Ghost::getTargetTilePosition() {
	return targetTilePosition;
}

void Ghost::flipWhichEdibleImage(bool b) {
	whichEdibleImage = b;
}

void Ghost::reverseDirection() {
	queuedReverseDirectionFlag = true;
}

void Ghost::setAlive(bool a) {
	alive = a;
}

void Ghost::setEdible(bool e) {
	edible = e;
}

void Ghost::setMode(SpriteMode m) {
	mode = m;
}

void Ghost::setInitialTilePosition(vector<int> itp) {
	initialTilePosition = itp;
	tilePosition = initialTilePosition;
}

void Ghost::setHomeTilePosition(vector<int> htp) {
	homeTilePosition = htp;
}