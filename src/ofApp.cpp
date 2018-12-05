#include "ofApp.h"

// Public Methods
void ofApp::setup() {
	// Set Window Name
	ofSetWindowTitle("Pac-Man");

	// Set frameRate
	ofSetFrameRate(frameRate);

	// Set currentState
	currentState = START;

	// Font
	ofTrueTypeFont::setGlobalDpi(72);
	crackman.load("crackman.ttf", 12, true, true);
	emulogic.load("emulogic.ttf", 12, true, true);

	// Background Color
	ofBackground(0, 0, 0);
	ofSetBackgroundAuto(false);

	// Background Music
	backgroundMusic.load("temp.mp3");
	backgroundMusic.setLoop(true);
	// backgroundMusic.play();

	// Setup Arduino
	setupSerial();

	// Setup Buttons
	singlePlayerButton.setup("Solo", ofColor(255, 255, 255), "emulogic.ttf", ofColor(0, 0, 0), 12);
	ofAddListener(singlePlayerButton.clicked, this, &ofApp::singlePlayerButtonListener);

	multiPlayerButton.setup("Versus", ofColor(255, 255, 255), "emulogic.ttf", ofColor(0, 0, 0), 12);
	ofAddListener(multiPlayerButton.clicked, this, &ofApp::singlePlayerButtonListener);

	// Resize
	windowResized(screenWidth, screenHeight);
}

void ofApp::setupSerial() {
	serial.listDevices();
	for (ofSerialDeviceInfo device : serial.getDeviceList()) {
		std::cout << "Device Name: " << device.getDeviceName() <<
			"        Device ID: " << device.getDeviceID() <<
			"        Device Path: " << device.getDevicePath() << std::endl;
	}
	serial.setup(port, baudRate);
}

void ofApp::update() {
	// Read Message From Serial
	if (serial.isInitialized()) {
		if (serial.available()) {
			incomingMessage = true;
		}

		// Force Entire Message To Be Read
		if (incomingMessage) {
			while (serial.available()) {
				char character = (char)serial.readByte();
				if (character == '\n') {
					incomingMessage = false;
					break;
				}
				else {
					if (character != '\r' || character != '\t') {
						serialMessage += character;
					}
				}
			}
		}
	}

	// Handle serialMessage
	if (serialMessage != "") {
		if (!incomingMessage) {
			keyPressed(std::stoul(serialMessage, nullptr, 16));
			serialMessage = "";
		}
	}

	// Game Logic
	if (currentState == IN_PROGRESS) {
		// SpriteMode
		if (frightenedTimer.count<std::chrono::seconds>() >= frightenedTimeMarker) {
			// Reset frightenedTimer
			frightenedTimer.reset();

			// Set SpriteMode And Edible
			pacman.setMode(modeMarkers[modeIndex]);

			for (Ghost *g : ghostsVector) {
				g->setMode(modeMarkers[modeIndex]);
				g->setEdible(false);
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
					g->setMode(modeMarkers[modeIndex]);
					if (g->isAlive()) {
						g->reverseDirection();
					}
				}

			}
		}

		// Update Sprites
		pacman.update();
		for (Ghost *g : ghostsVector) {
			g->update();
		}

		// Check For PowerPellet Consumption
		if (pacman.hasEatenPowerPellet()) {
			// Set SpriteModes And Edible
			pacman.setMode(FRIGHTENED);
			for (Ghost *g : ghostsVector) {
				g->setMode(FRIGHTENED);
				g->setEdible(true);
			}

			// Change From: ___ To FRIGHTENED vs FRIGHTENED To FRIGHTENED
			if (!frightenedTimer.isStarted()) {
				for (Ghost *g : ghostsVector) {
					g->reverseDirection();
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
			if ((pacman.getTilePosition() == g->getTilePosition() && g->isAlive())) {
				if (g->getMode() == FRIGHTENED) {
					if (g->isEdible()) {
						g->setEdible(false);
						g->setAlive(false);
					}
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
		for (size_t i = 0; i < currentBoard.size(); i++) {
			for (size_t j = 0; j < currentBoard[0].size(); j++) {
				if (currentBoard[i][j].isStandardPellet() || currentBoard[i][j].isPowerPellet()) {
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
			ofstream outputFile("data/highscores.txt", std::ios::trunc);
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
	// Redraw Background
	if (redrawBackgroundFlag) {
		ofSetColor(ofColor(0, 0, 0));
		ofDrawRectangle(0, 0, screenWidth, screenHeight);
		redrawBackgroundFlag = false;
	}

	// Set All Button's Visibility To False
	singlePlayerButton.setVisible(false);
	multiPlayerButton.setVisible(false);

	// State-Based Drawing Calls
	switch (currentState) {
	case START:
		drawLandingPage();
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
		if (currentState == GAME_OVER) {
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

void ofApp::windowResized(int w, int h) {
	// Update Width & Height
	screenWidth = w;
	screenHeight = h;

	// Tile Size
	tileSize = min(screenHeight / currentBoard.size(), screenWidth / currentBoard[0].size());

	// Fonts
	crackman.load("crackman.ttf", screenWidth / 7.5, true, true);
	emulogic.load("emulogic.ttf", tileSize, true, true);

	// Offsets
	centerOffset[0] = (screenWidth - (currentBoard[0].size() * tileSize)) / 2;
	centerOffset[1] = (screenHeight - (currentBoard.size() * tileSize)) / 2;

	// Button Resize
	singlePlayerButton.setPosition(0, 0);
	singlePlayerButton.setSize(crackman.stringWidth("PAC-MAN") / 3, crackman.stringHeight("PAC-MAN") / 1.5);
	singlePlayerButton.setFontSize(singlePlayerButton.getSize()[1] / 4);
	singlePlayerButton.setRadius(
		multiPlayerButton.getSize()[1] / 2, // Top Left
		0, // Top Right
		0, // Bottom Right
		multiPlayerButton.getSize()[1] / 2 // Bottom Left
	);

	multiPlayerButton.setPosition(0, 0);
	multiPlayerButton.setSize(crackman.stringWidth("PAC-MAN") / 3, crackman.stringHeight("PAC-MAN") / 1.5);
	multiPlayerButton.setFontSize(multiPlayerButton.getSize()[1] / 4);
	multiPlayerButton.setRadius(
		0, // Top Left
		multiPlayerButton.getSize()[1] / 2, // Top Right
		multiPlayerButton.getSize()[1] / 2, // Bottom Right
		0 // Bottom Left
	);

	// Sprite Resize
	pacman.resize(screenWidth, screenHeight, tileSize);
	for (Ghost *g : ghostsVector) {
		g->resize(screenWidth, screenHeight, tileSize);
	}
}

void ofApp::singlePlayerButtonListener(ofVec2f &e) {
	// Board
	// TODO: Insert Code To Take User Input Here
	board = new Board();

	// Flags
	redrawBackgroundFlag = true;

	// Set Sprites' homeTilePosition && initialTilePosition
	pacman.setInitialPosition(vector<int>{ 26, 14 });
	for (Ghost *g : ghostsVector) {
		if (g->getGhostType() == BLINKY) {
			g->setHomeTilePosition(vector<int>{ 0, (int)currentBoard[0].size() - 1 - 2 });
			g->setInitialTilePosition(vector<int>{ 4, 1 });
		}
		else if (g->getGhostType() == PINKY) {
			g->setHomeTilePosition(vector<int>{ 0, 2 });
			g->setInitialTilePosition(vector<int>{ 32, 26});
		}
		else if (g->getGhostType() == INKY) {
			g->setHomeTilePosition(vector<int>{ (int)currentBoard.size() - 1, (int)currentBoard[0].size() - 1 });
			g->setInitialTilePosition(vector<int>{ 4, 26 });
		}
		else if (g->getGhostType() == CLYDE) {
			g->setHomeTilePosition(vector<int>{ (int)currentBoard.size() - 1, 0 });
			g->setInitialTilePosition(vector<int>{ 32, 1 });
		}
	}

	// Set Sprites' initialTilePosition
	vector<vector<int>> ghostInitialTilePositions = vector<vector<int>>{ {4, 1}, {32, 26}, {4, 26}, {32, 1} };
	for (size_t i = 0; i < ghostsVector.size(); i++) {
		ghostsVector[i]->setInitialTilePosition(ghostInitialTilePositions[i]);
	}

	// Reset Game
	resetGame();
}

void ofApp::multiPlayerButtonListener(ofVec2f &e) {
	// Board
	// TODO: Insert Code To Take User Input Here
	board = new Board();

	// Flags
	redrawBackgroundFlag = true;

	// Set Sprites' homeTilePosition && initialTilePosition
	pacman.setInitialPosition(vector<int>{ 26, 14 });
	for (Ghost *g : ghostsVector) {
		if (g->getGhostType() == BLINKY) {
			g->setHomeTilePosition(vector<int>{ 0, (int)currentBoard[0].size() - 1 - 2 });
			g->setInitialTilePosition(vector<int>{ 4, 1 });
		}
		else if (g->getGhostType() == PINKY) {
			g->setHomeTilePosition(vector<int>{ 0, 2 });
			g->setInitialTilePosition(vector<int>{ 32, 26});
		}
		else if (g->getGhostType() == INKY) {
			g->setHomeTilePosition(vector<int>{ (int)currentBoard.size() - 1, (int)currentBoard[0].size() - 1 });
			g->setInitialTilePosition(vector<int>{ 4, 26 });
		}
		else if (g->getGhostType() == CLYDE) {
			g->setHomeTilePosition(vector<int>{ (int)currentBoard.size() - 1, 0 });
			g->setInitialTilePosition(vector<int>{ 32, 1 });
		}
	}

	// Set Sprites' initialTilePosition
	vector<vector<int>> ghostInitialTilePositions = vector<vector<int>>{ {4, 1}, {32, 26}, {4, 26}, {32, 1} };
	for (size_t i = 0; i < ghostsVector.size(); i++) {
		ghostsVector[i]->setInitialTilePosition(ghostInitialTilePositions[i]);
	}

	// Reset Game
	resetGame();
}

// Private Methods
void ofApp::drawLandingPage() {
	// Reset Canvas
	ofSetColor(0, 0, 0);
	ofDrawRectangle(0, 0, screenWidth, screenHeight);

	// Centering Variables
	vector<int> elementBuffer = { screenWidth / 125, (int)crackman.stringHeight("PAC-MAN") / 5 };
	int sumOfElementHeights = crackman.stringHeight("PAC-MAN") + elementBuffer[1] + max(singlePlayerButton.getSize()[1], multiPlayerButton.getSize()[1]);
	
	// "PACMAN" Horizontally And Vertically Centered With Respect To The Buttons And The Screen
	ofSetColor(255, 255, 0);
	crackman.drawString("PAC-MAN",
		(screenWidth - crackman.stringWidth("PAC-MAN")) / 2,
		(screenHeight - sumOfElementHeights) / 2 + crackman.stringHeight("PAC-MAN"));

	// Buttons Horitontally And Vertically Centered With Respect To "PACMAN", Each Other, And The Screen
	int sumOfButtonWidths = singlePlayerButton.getSize()[0] + elementBuffer[0] + multiPlayerButton.getSize()[0];

	singlePlayerButton.setVisible(true);
	singlePlayerButton.setPosition(
		(screenWidth - sumOfButtonWidths) / 2,
		(screenHeight - sumOfElementHeights) / 2 + crackman.stringHeight("PAC-MAN") + elementBuffer[1]);
	singlePlayerButton.draw();

	multiPlayerButton.setVisible(true);
	multiPlayerButton.setPosition(
		(screenWidth - sumOfButtonWidths) / 2 + singlePlayerButton.getSize()[0] + elementBuffer[0],
		(screenHeight - sumOfElementHeights) / 2 + crackman.stringHeight("PAC-MAN") + elementBuffer[1]);
	multiPlayerButton.draw();
}

void ofApp::drawGameBoard() {
	for (size_t i = 0; i < currentBoard.size(); i++) {
		for (size_t j = 0; j < currentBoard[0].size(); j++) {
			if (currentBoard[i][j].getID() == -1) {
				// Invalid Block
				ofSetColor(0, 0, 0);
				ofDrawRectangle(j * tileSize + centerOffset[0], i * tileSize + centerOffset[1], tileSize, tileSize);
			}
			else if (currentBoard[i][j].getID() == 0) {
				// Wall
				ofSetColor(50, 50, 255);
				ofDrawRectangle(j * tileSize + centerOffset[0], i * tileSize + centerOffset[1], tileSize, tileSize);
			}
			else if (currentBoard[i][j].getID() == 1) {
				if (currentBoard[i][j].isStandardPellet()) {
					// Tile
					ofSetColor(0, 0, 0);
					ofDrawRectangle(j * tileSize + centerOffset[0], i * tileSize + centerOffset[1], tileSize, tileSize);

					// Standard Pellet
					ofSetColor(255, 255, 0);
					ofDrawCircle((j + 0.5) * tileSize + centerOffset[0], (i + 0.5) * tileSize + centerOffset[1], tileSize / 8);
				}
				else if (currentBoard[i][j].isPowerPellet()) {
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
	vector<int> highScoreLabelTilePosition = { 1, (int)((currentBoard[0].size() - string("HIGH SCORE").length()) / 2) };

	// High Score Horizontally Centered With Respect To The Screen
	string highScore;
	if (pacman.getScore() > highScores[0]) {
		highScore = std::to_string(pacman.getScore());
	}
	else {
		highScore = std::to_string(highScores[0]);
	}
	vector<int> highScoreTilePosition = { 2,  (int)((currentBoard[0].size() - highScore.length()) / 2) };

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
	vector<int> tilePosition{ (int)currentBoard.size() - 1, 3 };
	for (int i = 0; i < pacman.getLives() - 1; i++) {
		ofSetColor(255, 255, 0);
		ofDrawCircle((tilePosition[1] + i * 2) * tileSize + centerOffset[0],
			(tilePosition[0]) * tileSize + centerOffset[1],
			tileSize);
	}
}

void ofApp::drawPacMan() {
	if (currentState == IN_PROGRESS) {
		if (pacman.getCurrentVelocity() == vector<int>{0, 0}) {
			angleDisplacement = 0;
			pacmanDegree = 0;
		}
		else {
			// pacmanDegree
			if (degreeFlag) {
				pacmanDegree += degreeIncrement;

				if (pacmanDegree >= maxDegree) {
					degreeFlag = false;
				}
			}
			else {
				pacmanDegree -= degreeIncrement;

				if (pacmanDegree <= 0) {
					degreeFlag = true;
				}
			}

			// angleDisplacement
			if (pacman.getCurrentVelocity() == vector<int>{0, -1}) {
				// Up
				angleDisplacement = 270;
			}
			else if (pacman.getCurrentVelocity() == vector<int>{-1, 0}) {
				// Left
				angleDisplacement = 180;
			}
			else if (pacman.getCurrentVelocity() == vector<int>{0, 1}) {
				// Down
				angleDisplacement = 90;
			}
			else if (pacman.getCurrentVelocity() == vector<int>{1, 0}) {
				// Right
				angleDisplacement = 0;
			}
		}
	}
	

	// Draw Pacman
	ofPath pacmanPath;
	pacmanPath.setColor(pacman.getDefaultColor());
	pacmanPath.setCircleResolution(360);
	pacmanPath.setFilled(true);
	pacmanPath.arc(pacman.getPixelPosition()[0] + centerOffset[0], pacman.getPixelPosition()[1] + centerOffset[1], 
		tileSize / 2, tileSize / 2, 
		angleDisplacement + pacmanDegree, angleDisplacement - pacmanDegree);
	pacmanPath.draw();
}

void ofApp::drawGhosts() {
	/*
	// Draw targetTile
	for (Ghost *g : ghostsVector) {
		ofSetColor(g->getDefaultColor());
		ofDrawRectangle(g->getTargetTilePixelPosition()[0] + centerOffset[0] - tileSize / 4,
			g->getTargetTilePixelPosition()[1] + centerOffset[1] - tileSize / 4,
			tileSize / 2, tileSize / 2);
	}
	*/

	for (Ghost *g : ghostsVector) {
		if (g->isEdible()) {
			if (frightenedTimer.count<std::chrono::milliseconds>() / 250 % 2) {
				g->flipWhichEdibleImage(true);
			}
			else {
				g->flipWhichEdibleImage(false);
			}
		}
		ofSetColor(255, 255, 255);
		g->getImage().draw(g->getPixelPosition()[0] - tileSize / 2 + centerOffset[0],
			g->getPixelPosition()[1] + centerOffset[1] - tileSize / 2,
			tileSize, tileSize);
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
	vector<int> initialTilePosition = { (int)(currentBoard.size() - (highScores.size() + 1)) / 2 + 1,
										(int)((currentBoard[0].size() - str.length()) / 2) };
	emulogic.drawString(str,
		initialTilePosition[1] * tileSize + centerOffset[0],
		initialTilePosition[0] * tileSize + centerOffset[1]);

	// Draw Scores
	for (int score : highScores) {
		str = std::to_string(score);
		initialTilePosition = vector<int>{ initialTilePosition[0] + 1,
										   (int)((currentBoard[0].size() - str.length()) / 2) };
		emulogic.drawString(str,
			initialTilePosition[1] * tileSize + centerOffset[0],
			initialTilePosition[0] * tileSize + centerOffset[1]);
	}
}

void ofApp::resetSprites() {
	// Reset Sprites
	pacman.resetLevel(level);
	for (Ghost *g : ghostsVector) {
		g->resetLevel(level);
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
	currentBoard = board->resetBoard();

	// Reset Sprites
	resetSprites();
}

void ofApp::resetGame() {
	// Read highscores From File
	ifstream inputFile("data/highscores.txt");
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
	currentBoard = board->resetBoard();

	// Set Level To 0
	level = 0;

	// Set Flags
	highScoreFlag = true;

	// Reset Game
	pacman.resetGame();
	for (Ghost *g : ghostsVector) {
		g->resetGame();
	}

	// Reset SpriteMode Variables
	modeTimer.reset();
	modeIndex = 0;

	// Set GameState
	currentState = PAUSED;
}