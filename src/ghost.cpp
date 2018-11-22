#include "Ghost.h"

// Constructors
Ghost::Ghost() {}

Ghost::~Ghost() {}

// Methods
void Ghost::update(vector<vector<Tile>> board, Pacman pacman) {
	// Calculate targetTile
	calculateTargetTile(pacman);

	// Update currentVelocity
	updateVelocity(board);

	// Move In The Direction Of currentVelocity
	move();

	// Adjust tilePosition To Stay In Bounds
	adjustBounds(board);
}

void Ghost::calculateTargetTile(Pacman pacman) {
	if (state == CHASE) {
		targetTile = pacman.getTilePosition();
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

void Ghost::updateVelocity(vector<vector<Tile>> board) {
	if (reverseDirectionFlag) {
		// Reverse Direction Of Travel
		currentVelocity[0] *= -1;
		currentVelocity[1] *= -1;

		reverseDirectionFlag = false;
	}
	else {
		// Update currentVelocity To queuedVelocity If Ghost Is Within (Speed / 2) Ticks Of The Center Of The Tile
		if (abs(currentTick[0] - maxTick / 2) < (epsilon + speed / 2) && abs(currentTick[1] - maxTick / 2) < (epsilon + speed / 2)) {
			// Retrieve Valid Velocities From queuedVelocity And Append It To possibleVelocity
			vector<vector<int>> possibleVelocity{};

			for (int i = 0; i < 4; i++) {
				if (checkValidVelocity(board, queuedVelocity[i])) {
					possibleVelocity.push_back(queuedVelocity[i]);
				}
			}

			// Determine The Velocity Which Yields In Closest Distance To targetTile
			int minIndex = -1;
			double minVal = 1000000000.0;

			for (size_t i = 0; i < possibleVelocity.size(); i++) {
				double distance = calculateDistance(tileSize * (targetTile[0] + 0.5),
					tileSize * (targetTile[1] + 0.5),
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

bool Ghost::checkValidVelocity(vector<vector<Tile>> board, vector<int> velocity) {
	if (velocity == vector<int>{0, 0}) {
		return true;
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

// Reset Functions
void Ghost::resetLevel(int l) {
	level = l;

	tilePosition = initialTilePosition;
	currentTick = vector<double>{ maxTick / 2, maxTick / 2 };

	currentVelocity = { 0, 0 };
}

void Ghost::resetGame() {
	level = 0;

	tilePosition = initialTilePosition;
	currentTick = vector<double>{ maxTick / 2, maxTick / 2 };

	currentVelocity = { 0, 0 };
}

// Getters
vector<double> Ghost::getPixelPosition() {
	return vector<double>{ (tilePosition[1] + (currentTick[1] / maxTick)) * tileSize,
		(tilePosition[0] + (currentTick[0] / maxTick)) * tileSize };
}

vector<int> Ghost::getTilePosition() {
	return tilePosition;
}

vector<double> Ghost::getTargetTilePixelPosition() {
	return vector<double>{ (targetTile[1] + 0.5) * tileSize, (targetTile[0] + 0.5) * tileSize };
}

vector<int> Ghost::getTargetTile() {
	return targetTile;
}

// Setters
void Ghost::reverseDirection() {
	reverseDirectionFlag = true;
}

void Ghost::setState(SpriteState s) {
	state = s;
}

void Ghost::setHomeTilePosition(vector<int> htp) {
	homeTilePosition = htp;
}

void Ghost::setInitialTilePosition(vector<int> itp) {
	initialTilePosition = itp;
	tilePosition = initialTilePosition;
}

void Ghost::resize(int w, int h, int ts) {
	screenWidth = w;
	screenHeight = h;
	tileSize = ts;

	speed = maxTick * tilesPerSecond / frameRate;
}