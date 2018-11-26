#include "ofApp.h"

// Public Methods
void ofApp::setup() {
	// Set Window Name
	ofSetWindowTitle("Pac-Man");

	// Set frameRate
	ofSetFrameRate(frameRate);

	// Background Color
	ofBackground(0, 0, 0);
	ofSetBackgroundAuto(false);

	// Background Music
	backgroundMusic.load("temp.mp3");
	backgroundMusic.setLoop(true);
	// backgroundMusic.play();

	// Font - Loaded In windowsResized
	ofTrueTypeFont::setGlobalDpi(72);

	// Set currentState
	currentState = START;

	// Resize
	windowResized(screenWidth, screenHeight);
}

void ofApp::update() {
	if (currentState == IN_PROGRESS) {
		// SpriteMode
		if (frightenedTimer.count<std::chrono::seconds>() >= frightenedTimeMarker) {
			// Reset frightenedTimer
			frightenedTimer.reset();

			// Set SpriteMode And Edible
			pacman.setMode(modeMarkers[modeIndex]);

			for (Ghost *g : ghostsVector) {
				(*g).setMode(modeMarkers[modeIndex]);
				(*g).setEdible(false);
			}

			// Continue modeTimer
			modeTimer.start();
		}
		else {
			if (!modeTimer.isStarted()) {
				modeTimer.start();
			}

			if (modeTimer.count<std::chrono::seconds>() >= modeTimeMarkers[modeIndex]) {
				// Variable Increment/Reset
				modeIndex++;
				modeTimer.reset();

				// Set SpriteModes And reverseDirection
				pacman.setMode(modeMarkers[modeIndex]);
				for (Ghost *g : ghostsVector) {
					(*g).setMode(modeMarkers[modeIndex]);
					if ((*g).isAlive()) {
						(*g).reverseDirection();
					}
				}

			}
		}

		// Update Sprites
		pacman.update();
		for (Ghost *g : ghostsVector) {
			(*g).update();
		}

		// Check For PowerPellet Consumption
		if (pacman.hasEatenPowerPellet()) {
			// Set SpriteModes And Edible
			pacman.setMode(FRIGHTENED);
			for (Ghost *g : ghostsVector) {
				(*g).setMode(FRIGHTENED);
				(*g).setEdible(true);
			}

			// Change From: ___ To FRIGHTENED vs FRIGHTENED To FRIGHTENED
			if (!frightenedTimer.isStarted()) {
				for (Ghost *g : ghostsVector) {
					(*g).reverseDirection();
				}

				frightenedTimer.start();
			}
			else {
				frightenedTimer.reset();
				frightenedTimer.start();
			}

			// Stop modeTimer
			modeTimer.stop();
		}

		// Check For Pacman - Ghost Collision
		for (Ghost *g : ghostsVector) {
			if ((pacman.getTilePosition() == (*g).getTilePosition() && (*g).isAlive())) {
				if ((*g).isEdible()) {
					if ((*g).getMode() != FRIGHTENED) {
						std::cerr << "Error. Ghost Is Edible But Not In FRIGHTENED Mode." << std::endl;
						std::exit(1);
					}
					(*g).setAlive(false);
				}
				else {
					// Decrement Lives
					pacman.decrementLives();

					// Reset Sprites
					resetSprites();
				}
			}
		}

		// Check For Next Level
		for (size_t i = 0; i < board.size(); i++) {
			for (size_t j = 0; j < board[0].size(); j++) {
				if (board[i][j].isStandardPellet() || board[i][j].isPowerPellet()) {
					goto stop;
				}
			}
		}
		level++;
		resetLevel();
	stop:

		// Check For State Changes
		if (pacman.getLives() == 0) {
			currentState = GAME_OVER;
		}
	}
	else if (currentState == GAME_OVER) {
		if (highScoreFlag) {
			// Reorder highscores
			highScores.push_back(pacman.getScore());
			std::sort(highScores.begin(), highScores.end(), std::greater<>());
			highScores.pop_back();

			// Write highscores To File
			ofstream outputFile("highscores.txt", std::ios::trunc);
			if (outputFile.is_open()) {
				for (int i = 0; i < 10; i++) {
					outputFile << highScores[i] << "\n";
				}
				outputFile.close();
			}
			else {
				std::cerr << "Error. Unable To Open File" << std::endl;
				std::exit(1);
			}

			// Change Flag
			highScoreFlag = false;
		}
	}
}

void ofApp::draw() {
	switch (currentState) {
	case START:
		drawLandingPage();
		break;
	case INSTRUCTIONS:
		drawInstructions();
		break;
	case IN_PROGRESS:
		// Fallthrough Intended
	case PAUSED:
		drawGameBoard();
		drawMisc();
		drawPacMan();
		drawGhosts();
		break;
	case GAME_OVER:
		drawGameOver();
		break;
	case HIGH_SCORE:
		drawHighScores();
		break;
	default:
		// Exit With Error Message
		std::cerr << "Error. GameState Is Invalid" << std::endl;
		std::exit(1);
	}
}

void ofApp::keyPressed(int key) {
	// TODO: Remove
	if (key == OF_KEY_CONTROL) {
		// Flip State
		if (currentState == START) {
			currentState = INSTRUCTIONS;
		}
		else if (currentState == INSTRUCTIONS) {
			// Set Sprites' homeTilePosition && initialTilePosition
			pacman.setInitialPosition(vector<int>{ 26, 14 });
			for (Ghost *g : ghostsVector) {
				if ((*g).getGhostType() == BLINKY) {
					(*g).setHomeTilePosition(vector<int>{ 0, (int)board[0].size() - 1 - 2 });
					(*g).setInitialTilePosition(vector<int>{ 4, 1 });
				}
				else if ((*g).getGhostType() == PINKY) {
					(*g).setHomeTilePosition(vector<int>{ 0, 2 });
					(*g).setInitialTilePosition(vector<int>{ 32, 26});
				}
				else if ((*g).getGhostType() == INKY) {
					(*g).setHomeTilePosition(vector<int>{ (int)board.size() - 1, (int)board[0].size() - 1 });
					(*g).setInitialTilePosition(vector<int>{ 4, 26 });
				}
				else if ((*g).getGhostType() == CLYDE) {
					(*g).setHomeTilePosition(vector<int>{ (int)board.size() - 1, 0 });
					(*g).setInitialTilePosition(vector<int>{ 32, 1 });
				}
			}

			// Set Sprites' initialTilePosition
			vector<vector<int>> ghostInitialTilePositions = vector<vector<int>>{ {4, 1}, {32, 26}, {4, 26}, {32, 1} };
			for (size_t i = 0; i < ghostsVector.size(); i++) {
				(*(ghostsVector[i])).setInitialTilePosition(ghostInitialTilePositions[i]);
			}

			// Reset Game
			resetGame();
		}
		else if (currentState == GAME_OVER) {
			currentState = HIGH_SCORE;
		}
		else if (currentState == HIGH_SCORE) {
			resetGame();
			currentState = START;
		}
	}

	// Fullscreen
	if (key == OF_KEY_F12) {
		ofToggleFullscreen();
	}

	// Pause || WASD
	int upper_key = toupper(key);
	if (upper_key == 'P') {
		// Flip current_state_
		if (currentState == IN_PROGRESS) {
			currentState = PAUSED;
		}
		else if (currentState == PAUSED) {
			currentState = IN_PROGRESS;
		}
		return;
	}
	else if (currentState == IN_PROGRESS) {
		if (upper_key == 'W') {
			pacman.setQueuedVelocity({ 0, -1 });
		}
		else if (upper_key == 'A') {
			pacman.setQueuedVelocity({ -1, 0 });
		}
		else if (upper_key == 'S') {
			pacman.setQueuedVelocity({ 0, 1 });
		}
		else if (upper_key == 'D') {
			pacman.setQueuedVelocity({ 1, 0 });
		}
	}
}

void ofApp::mousePressed(int x, int y, int button) {

}

void ofApp::windowResized(int w, int h) {
	// Update Width & Height
	screenWidth = w;
	screenHeight = h;

	// Tile Size
	tileSize = min(screenHeight / board.size(), screenWidth / board[0].size());

	// Fonts
	crackman.load("crackman.ttf", screenHeight / 10, true, true);
	emulogic.load("emulogic.ttf", tileSize, true, true);

	// Offsets
	centerOffset[0] = (screenWidth - (board[0].size() * tileSize)) / 2;
	centerOffset[1] = (screenHeight - (board.size() * tileSize)) / 2;

	// Resize
	pacman.resize(screenWidth, screenHeight, tileSize);
	for (Ghost *g : ghostsVector) {
		(*g).resize(screenWidth, screenHeight, tileSize);
	}
}

// Private Methods
void ofApp::drawLandingPage() {
	// Reset Canvas
	ofSetColor(0, 0, 0);
	ofDrawRectangle(0, 0, screenWidth, screenHeight);

	// "PACMAN" Horizontally And Vertically Centered With Respect To The Screen
	ofSetColor(255, 255, 0);
	crackman.drawString("PAC-MAN",
		(screenWidth - crackman.stringWidth("PAC-MAN")) / 2,
		(screenHeight - crackman.stringHeight("PAC-MAN")) / 2);
}

void ofApp::drawInstructions() {
	// Reset Canvas
	ofSetColor(0, 0, 0);
	ofDrawRectangle(0, 0, screenWidth, screenHeight);

	// "INSTRUCTIONS"
	ofSetColor(255, 255, 255);
	emulogic.drawString("INSTRUCTIONS",
		(screenWidth - emulogic.stringWidth("INSTRUCTIONS")) / 2,
		(screenHeight - emulogic.stringHeight("INSTRUCTIONS")) / 2);
}

void ofApp::drawGameBoard() {
	for (size_t i = 0; i < board.size(); i++) {
		for (size_t j = 0; j < board[0].size(); j++) {
			if (board[i][j].getID() == -1) {
				// Invalid Block
				ofSetColor(0, 0, 0);
				ofDrawRectangle(j * tileSize + centerOffset[0], i * tileSize + centerOffset[1], tileSize, tileSize);
			}
			else if (board[i][j].getID() == 0) {
				// Wall
				ofSetColor(50, 50, 255);
				ofDrawRectangle(j * tileSize + centerOffset[0], i * tileSize + centerOffset[1], tileSize, tileSize);
			}
			else if (board[i][j].getID() == 1) {
				if (board[i][j].isStandardPellet()) {
					// Tile
					ofSetColor(0, 0, 0);
					ofDrawRectangle(j * tileSize + centerOffset[0], i * tileSize + centerOffset[1], tileSize, tileSize);

					// Standard Pellet
					ofSetColor(255, 255, 0);
					ofDrawCircle((j + 0.5) * tileSize + centerOffset[0], (i + 0.5) * tileSize + centerOffset[1], tileSize / 8);
				}
				else if (board[i][j].isPowerPellet()) {
					// Tile
					ofSetColor(0, 0, 0);
					ofDrawRectangle(j * tileSize + centerOffset[0], i * tileSize + centerOffset[1], tileSize, tileSize);

					// Power Pellet
					ofSetColor(255, 255, 0);
					ofDrawCircle((j + 0.5) * tileSize + centerOffset[0], (i + 0.5) * tileSize + centerOffset[1], tileSize / 2.5);
				}
				else {
					// Tile
					ofSetColor(0, 0, 0);
					ofDrawRectangle(j * tileSize + centerOffset[0], i * tileSize + centerOffset[1], tileSize, tileSize);

					// No Pellet
				}
			}
			else {
				// Exit With Error Message
				std::cerr << "Error. GameBoard Is Invalid" << std::endl;
				std::exit(1);
			}
		}
	}
}

void ofApp::drawMisc() {
	ofSetColor(255, 255, 255);

	// "HIGH SCORE" Horizontally Centered With Respect To The Screen
	vector<int> highScoreLabelTilePosition = { 1, (int)((board[0].size() - string("HIGH SCORE").length()) / 2) };

	// High Score Horizontally Centered With Respect To The Screen
	string highScore;
	if (pacman.getScore() > highScores[0]) {
		highScore = std::to_string(pacman.getScore());
	}
	else {
		highScore = std::to_string(highScores[0]);
	}
	vector<int> highScoreTilePosition = { 2,  (int)((board[0].size() - highScore.length()) / 2) };

	// "1UP" Horizontally Centered With Respect To "HIGH SCORE"
	vector<int> playerLabelTilePosition = { 1, (int)((highScoreLabelTilePosition[1] - string("1UP").length()) / 2) };

	// "Rightermost Entry Of Score Is One Tile After End Of "1UP"
	string currentScore = std::to_string(pacman.getScore());
	vector<int> currentScoreTilePosition = { 2, (int)(playerLabelTilePosition[1] + string("1UP").length() + 1 - currentScore.length()) };

	// Draw
	emulogic.drawString("HIGH SCORE",
		highScoreLabelTilePosition[1] * tileSize + centerOffset[0],
		highScoreLabelTilePosition[0] * tileSize + centerOffset[1]);
	emulogic.drawString(highScore,
		highScoreTilePosition[1] * tileSize + centerOffset[0],
		highScoreTilePosition[0] * tileSize + centerOffset[1]);

	emulogic.drawString("1UP",
		playerLabelTilePosition[1] * tileSize + centerOffset[0],
		playerLabelTilePosition[0] * tileSize + centerOffset[1]);
	emulogic.drawString(currentScore,
		currentScoreTilePosition[1] * tileSize + centerOffset[0],
		currentScoreTilePosition[0] * tileSize + centerOffset[1]);

	// Lives
	vector<int> tilePosition{ (int)board.size() - 1, 3 };
	for (int i = 0; i < pacman.getLives() - 1; i++) {
		ofSetColor(255, 255, 0);
		ofDrawCircle((tilePosition[1] + i * 2) * tileSize + centerOffset[0],
			(tilePosition[0]) * tileSize + centerOffset[1],
			tileSize);
	}
}

void ofApp::drawPacMan() {
	ofSetColor(255, 255, 0);
	ofDrawCircle(pacman.getPixelPosition()[0] + centerOffset[0], pacman.getPixelPosition()[1] + centerOffset[1], tileSize / 2);
}

void ofApp::drawGhosts() {
	for (Ghost *g : ghostsVector) {
		if ((*g).isAlive()) {
			ofSetColor((*g).getColor()[0], (*g).getColor()[1], (*g).getColor()[2]);
			if ((*g).isEdible()) {
				if (frightenedTimer.count<std::chrono::milliseconds>() / 250 % 2) {
					ofSetColor(25, 25, 255);
				}
				else {
					ofSetColor(255, 255, 255);
				}
			}
		}
		else {
			ofSetColor(255, 255, 255);
			//ofSetColor((*g).getColor()[0] * 0.75, (*g).getColor()[1] * 0.75, (*g).getColor()[2] * 0.75);
		}
		ofDrawCircle((*g).getPixelPosition()[0] + centerOffset[0], (*g).getPixelPosition()[1] + centerOffset[1], tileSize / 2);
		ofDrawRectangle((*g).getTargetTilePixelPosition()[0] + centerOffset[0] - tileSize / 4,
			(*g).getTargetTilePixelPosition()[1] + centerOffset[1] - tileSize / 4,
			tileSize / 2, tileSize / 2);
	}
}

void ofApp::drawGameOver() {

}

void ofApp::drawHighScores() {
	ofSetColor(0, 0, 0);
	ofDrawRectangle(0, 0, screenWidth, screenHeight);

	ofSetColor(255, 255, 255);

	// Draw "HIGH SCORES"
	string str = "HIGH SCORES";
	vector<int> initialTilePosition = { (int)(board.size() - (highScores.size() + 1)) / 2 + 1,
										(int)((board[0].size() - str.length()) / 2) };
	emulogic.drawString(str,
		initialTilePosition[1] * tileSize + centerOffset[0],
		initialTilePosition[0] * tileSize + centerOffset[1]);

	// Draw Scores
	for (int score : highScores) {
		str = std::to_string(score);
		initialTilePosition = vector<int>{ initialTilePosition[0] + 1,
										   (int)((board[0].size() - str.length()) / 2) };
		emulogic.drawString(str,
			initialTilePosition[1] * tileSize + centerOffset[0],
			initialTilePosition[0] * tileSize + centerOffset[1]);
	}
}

void ofApp::resetSprites() {
	// Reset Sprites
	pacman.resetLevel(level);
	for (Ghost *g : ghostsVector) {
		(*g).resetLevel(level);
	}

	// Reset SpriteMode Variables
	modeTimer.reset();
	modeIndex = 0;

	frightenedTimer.reset();

	// Set GameState
	currentState = PAUSED;
}

void ofApp::resetLevel() {
	// New Board
	board = Board().getBoard();

	// Reset Sprites
	resetSprites();
}

void ofApp::resetGame() {
	// Read highscores From File
	ifstream inputFile("highscores.txt");
	if (inputFile.is_open()) {
		int lineCount = 0;
		string line;
		while (getline(inputFile, line)) {
			highScores[lineCount] = std::stoi(line);
			lineCount++;
		}

		inputFile.close();
	}
	else {
		std::cerr << "Error. Unable To Open File" << std::endl;
		std::exit(1);
	}

	// Create A New Board
	board = Board().getBoard();

	// Set Level To 0
	level = 0;

	// Set Flags
	highScoreFlag = true;

	// Reset Game
	pacman.resetGame();
	for (Ghost *g : ghostsVector) {
		(*g).resetGame();
	}

	// Reset SpriteMode Variables
	modeTimer.reset();
	modeIndex = 0;

	// Set GameState
	currentState = PAUSED;
}