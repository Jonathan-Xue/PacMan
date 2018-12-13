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
	singlePlayerButton.setup("Start", ofColor(255, 255, 255), "emulogic.ttf", ofColor(0, 0, 0), 12);
	ofAddListener(singlePlayerButton.clicked, this, &ofApp::singlePlayerButtonListener);

	continueButton.setup("Continue", ofColor(255, 0, 0), "emulogic.ttf", ofColor(255, 255, 255), 12);
	ofAddListener(continueButton.clicked, this, &ofApp::continueButtonListener);

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
	if (currentState == LEVEL_EDITOR) {
		if (currentEditorOption == ROW_ADJUSTMENT || currentEditorOption == COL_ADJUSTMENT) {
			bool adjustmentFlag = false;

			// Row Adjustments
			while ((unsigned)levelEditorPanel.getRows() != currentBoard.size()) {
				if ((unsigned)levelEditorPanel.getRows() > currentBoard.size()) {
					vector<Tile> temp;
					for (unsigned i = 0; i < currentBoard[0].size(); i++) {
						temp.push_back(Tile(0, false, false));
					}
					currentBoard.insert(currentBoard.begin() + currentBoard.size(), temp);
				}
				else if ((unsigned)levelEditorPanel.getRows() < currentBoard.size()) {
					currentBoard.erase(currentBoard.begin() + (currentBoard.size() - 1));
				}

				adjustmentFlag = true;
			}

			// Column Adjustments
			while ((unsigned)levelEditorPanel.getCols() != currentBoard[0].size()) {
				if ((unsigned)levelEditorPanel.getCols() > currentBoard[0].size()) {
					for (unsigned i = 0; i < currentBoard.size(); i++) {
						currentBoard[i].push_back(Tile(0, false, false));
					}
				}
				else if ((unsigned)levelEditorPanel.getCols() < currentBoard[0].size()) {
					for (unsigned i = 0; i < currentBoard.size(); i++) {
						currentBoard[i].pop_back();
					}
				}

				adjustmentFlag = true;
			}

			// Adjust Display Variables
			if (adjustmentFlag) {
				windowResized(screenWidth, screenHeight);
			}
		}
	}
	else if (currentState == IN_PROGRESS) {
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
			// if ((pacman.getTilePosition() == g->getTilePosition() && g->isAlive())) { --> Doesn't Trigger If Pacman & Ghost Switch Tiles Perfectly
			if (ofRectangle(pacman.getTopLeftPixelPosition()[0], pacman.getTopLeftPixelPosition()[1], tileSize, tileSize).intersects(
				ofRectangle(g->getTopLeftPixelPosition()[0], g->getTopLeftPixelPosition()[1], tileSize, tileSize)) && g->isAlive()) {
				if (g->getMode() == FRIGHTENED && g->isEdible()) {
					pacman.incrementScore(pointsPerGhost);
					g->setEdible(false);
					g->setAlive(false);
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
		for (unsigned i = 0; i < currentBoard.size(); i++) {
			for (unsigned j = 0; j < currentBoard[0].size(); j++) {
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
		ofBackground(ofColor(0, 0, 0));
		redrawBackgroundFlag = false;
	}

	// Set All Button's Visibility To False
	singlePlayerButton.setVisible(false);
	continueButton.setVisible(false);

	// State-Based Drawing Calls
	switch (currentState) {
	case START:
		drawLandingPage();
		break;
	case LEVEL_EDITOR:
		drawLevelEditor();
		redrawBackgroundFlag = true;
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

void ofApp::mousePressed(ofMouseEventArgs &args) {
	// Level Editor
	if (currentState == LEVEL_EDITOR) {
		// Ignore Panel
		if (!levelEditorPanel.withinBounds(args.x, args.y)) {
			vector<int> tilePosition = vector<int>{ ((int)args.y - centerOffset[1]) / tileSize - tileBuffer[0], ((int)args.x - centerOffset[0]) / tileSize - tileBuffer[1] };
			// Prevent Elements From Being Placed Outside Of Board (Will Throw OutOfBounds Error)
			if ((tilePosition[0] >= 0 && tilePosition[0] < (int)currentBoard.size() &&
				tilePosition[1] >= 0 && tilePosition[1] < (int)currentBoard[0].size())) {
				switch (currentEditorOption) {
				case ROW_ADJUSTMENT:
				case COL_ADJUSTMENT:
					break;
				case WALL_BLOCK:
					currentBoard[tilePosition[0]][tilePosition[1]].setParams(0, false, false);
					break;
				case PATH_BLOCK:
					currentBoard[tilePosition[0]][tilePosition[1]].setParams(1, false, false);
					break;
				case STANDARD_PELLET_BLOCK:
					currentBoard[tilePosition[0]][tilePosition[1]].setParams(1, true, false);
					break;
				case POWER_PELLET_BLOCK:
					currentBoard[tilePosition[0]][tilePosition[1]].setParams(1, false, true);
					break;
				case PACMAN_SPRITE:
					pacman.setInitialTilePosition(tilePosition);
					break;
				case BLINKY_SPRITE:
					blinky.setInitialTilePosition(tilePosition);
					break;
				case BLINKY_HOME_TILE:
					blinky.setHomeTilePosition(tilePosition);
					break;
				case PINKY_SPRITE:
					pinky.setInitialTilePosition(tilePosition);
					break;
				case PINKY_HOME_TILE:
					pinky.setHomeTilePosition(tilePosition);
					break;
				case INKY_SPRITE:
					inky.setInitialTilePosition(tilePosition);
					break;
				case INKY_HOME_TILE:
					inky.setHomeTilePosition(tilePosition);
					break;
				case CLYDE_SPRITE:
					clyde.setInitialTilePosition(tilePosition);
					break;
				case CLYDE_HOME_TILE:
					clyde.setHomeTilePosition(tilePosition);
					break;
				default:
					std::cerr << "Error. Invalid editorOptions Enum. Verify That The Corresponding Enum Is Handled Within ofApp::mousePressed" << std::endl;
					std::exit(1);
					break;
				}
			}
		}
	}
}

void ofApp::mouseDragged(ofMouseEventArgs &args) {
	mousePressed(args);
}

void ofApp::keyPressed(int key) {
	// TODO: Remove
	if (key == OF_KEY_CONTROL) {
		if (currentState == HIGH_SCORE) {
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
	// Flags
	redrawBackgroundFlag = true;

	// Update Width & Height
	screenWidth = w;
	screenHeight = h;

	// Tile Size
	tileSize = min(screenHeight / (currentBoard.size() + tileBuffer[0] + tileBuffer[2]),
		screenWidth / (currentBoard[0].size() + tileBuffer[1] + tileBuffer[3]));

	// Fonts
	crackman.load("crackman.ttf", screenWidth / 7.5, true, true);
	emulogic.load("emulogic.ttf", tileSize, true, true);

	// Offsets
	centerOffset[0] = ((screenWidth - (currentBoard[0].size() * tileSize) - (tileBuffer[1] * tileSize) - (tileBuffer[3]) * tileSize)) / 2;
	centerOffset[1] = ((screenHeight - (currentBoard.size() * tileSize) - (tileBuffer[0] * tileSize) - (tileBuffer[2]) * tileSize)) / 2;

	// Button Resize
	singlePlayerButton.setPosition(0, 0);
	singlePlayerButton.setSize(crackman.stringWidth("PAC-MAN") / 3, crackman.stringHeight("PAC-MAN") / 1.5);
	singlePlayerButton.setFontSize(singlePlayerButton.getSize()[1] / 4);
	singlePlayerButton.setRadius(
		singlePlayerButton.getSize()[1] / 2, // Top Left
		singlePlayerButton.getSize()[1] / 2, // Top Right
		singlePlayerButton.getSize()[1] / 2, // Bottom Right
		singlePlayerButton.getSize()[1] / 2 // Bottom Left
	);

	continueButton.setPosition(0, 0);
	continueButton.setSize(currentBoard[0].size() * tileSize, tileBuffer[2] * tileSize);
	continueButton.setFontSize(tileSize);

	// Sprite Resize
	pacman.resize(screenWidth, screenHeight, tileSize);
	for (Ghost *g : ghostsVector) {
		g->resize(screenWidth, screenHeight, tileSize);
	}
}

void ofApp::singlePlayerButtonListener(ofVec2f &e) {
	// Flags
	redrawBackgroundFlag = true;

	// Board
	board = new BoardGenerator();

	// Set Sprites' initialTilePosition
	vector<vector<int>> ghostInitialTilePositions = vector<vector<int>>{ {1, 1}, {29, 26}, {1, 26}, {29, 1} };
	vector<vector<int>> ghostHomeTilePositions = vector<vector<int>>{ { 0, 27 }, { 0, 0 }, { 30, 27 }, { 30, 0 } };

	pacman.setInitialTilePosition(vector<int>{ 23, 14 });
	for (unsigned i = 0; i < ghostsVector.size(); i++) {
		ghostsVector[i]->setHomeTilePosition(ghostHomeTilePositions[i]);
		ghostsVector[i]->setInitialTilePosition(ghostInitialTilePositions[i]);
	}

	// State
	currentState = LEVEL_EDITOR;
}

void ofApp::continueButtonListener(ofVec2f &e) {
	if (currentState == LEVEL_EDITOR) {
		// OutOfBounds
		bool pacmanOutOfBounds = pacman.getTilePosition()[0] < 0 || (unsigned)pacman.getTilePosition()[0] >= currentBoard.size() ||
			pacman.getTilePosition()[1] < 0 || (unsigned)pacman.getTilePosition()[1] >= currentBoard[1].size();
		bool ghostOutOfBounds = false;
		for (Ghost *g : ghostsVector) {
			if (g->getTilePosition()[0] < 0 || (unsigned)g->getTilePosition()[0] >= currentBoard.size() ||
				g->getTilePosition()[1] < 0 || (unsigned)g->getTilePosition()[1] >= currentBoard[1].size()) {
				ghostOutOfBounds = true;
				break;
			}
		}

		// Verify Board Validity
		if (pacmanOutOfBounds || ghostOutOfBounds) {
			ofSystemAlertDialog("Error! The Current Board Is Invalid! All Sprites Must Be Within Board Bounds!");
		}
		else {
			// Set Board
			board->generateStringFromBoard(currentBoard);

			// Reset Game
			resetGame();
		}
	}
	else if (currentState == GAME_OVER) {
		currentState = HIGH_SCORE;
	}
	else if (currentState == HIGH_SCORE) {
		currentState = START;
	}
}

// Private Methods
void ofApp::drawLandingPage() {
	// Reset Canvas
	ofBackground(ofColor(0, 0, 0));

	// Centering Variables
	vector<int> elementBuffer = { screenWidth / 125, (int)crackman.stringHeight("PAC-MAN") / 5 };

	// "PAC-MAN" Horizontally And Vertically Centered With Respect To The Buttons And The Screen
	ofSetColor(ofColor(255, 255, 0));
	crackman.drawString("PAC-MAN",
		(screenWidth - crackman.stringWidth("PAC-MAN")) / 2,
		(screenHeight - crackman.stringHeight("PAC-MAN") - singlePlayerButton.getSize()[1]) / 2 + crackman.stringHeight("PAC-MAN"));

	// SinglePlayerButton Horizontall And Vertically Centered With Respect To "PAC-MAN" And The Screen
	singlePlayerButton.setPosition(
		(screenWidth - singlePlayerButton.getSize()[0]) / 2,
		(screenHeight - crackman.stringHeight("PAC-MAN") - singlePlayerButton.getSize()[1]) / 2 + crackman.stringHeight("PAC-MAN") + elementBuffer[1]);
	singlePlayerButton.setVisible(true);
	singlePlayerButton.draw();
}

void ofApp::drawLevelEditor() {
	// GameBoard
	drawGameBoard();

	// Sprites
	ofSetColor(pacman.getDefaultColor());
	ofDrawRectangle((pacman.getInitialTilePosition()[1] * tileSize) + (tileBuffer[1] * tileSize) + centerOffset[0],
		(pacman.getInitialTilePosition()[0] * tileSize) + (tileBuffer[0] * tileSize) + centerOffset[1],
		tileSize, tileSize);

	for (Ghost *g : ghostsVector) {
		ofSetColor(g->getDefaultColor());
		ofDrawRectangle((g->getInitialTilePosition()[1] * tileSize) + (tileBuffer[1] * tileSize) + centerOffset[0],
			(g->getInitialTilePosition()[0] * tileSize) + (tileBuffer[0] * tileSize) + centerOffset[1],
			tileSize, tileSize);

		ofColor darkenedColor = g->getDefaultColor();
		darkenedColor.setBrightness(160);
		ofSetColor(darkenedColor);
		ofDrawRectangle((g->getHomeTilePosition()[1] * tileSize) + (tileBuffer[1] * tileSize) + centerOffset[0],
			(g->getHomeTilePosition()[0] * tileSize) + (tileBuffer[0] * tileSize) + centerOffset[1],
			tileSize, tileSize);
	}

	// Grey Border
	ofNoFill();
	ofSetColor(ofColor(175, 175, 175));
	for (unsigned i = 0; i < currentBoard.size(); i++) {
		for (unsigned j = 0; j < currentBoard[0].size(); j++) {
			ofDrawRectangle((j * tileSize) + (tileBuffer[1] * tileSize) + centerOffset[0],
				(i * tileSize) + (tileBuffer[0] * tileSize) + centerOffset[1],
				tileSize, tileSize);
		}
	}
	ofFill();

	// Buttons
	continueButton.setPosition((tileBuffer[1] * tileSize) + centerOffset[0],
		(currentBoard.size() * tileSize) + (tileBuffer[0] * tileSize) + centerOffset[1]);
	continueButton.setVisible(true);
	continueButton.draw();

	// Level Editor Panel
	levelEditorPanel.draw();
}

void ofApp::drawGameBoard() {
	for (unsigned i = 0; i < currentBoard.size(); i++) {
		for (unsigned j = 0; j < currentBoard[0].size(); j++) {
			if (currentBoard[i][j].getID() == -1) {
				// Invalid Block
				ofSetColor(ofColor(0, 0, 0));
				ofDrawRectangle((j * tileSize) + (tileBuffer[1] * tileSize) + centerOffset[0],
					(i * tileSize) + (tileBuffer[0] * tileSize) + centerOffset[1], tileSize, tileSize);
			}
			else if (currentBoard[i][j].getID() == 0) {
				// Wall
				ofSetColor(ofColor(50, 50, 255));
				ofDrawRectangle((j * tileSize) + (tileBuffer[1] * tileSize) + centerOffset[0],
					(i * tileSize) + (tileBuffer[0] * tileSize) + centerOffset[1], tileSize, tileSize);
			}
			else if (currentBoard[i][j].getID() == 1) {
				if (currentBoard[i][j].isStandardPellet()) {
					// Tile
					ofSetColor(ofColor(0, 0, 0));
					ofDrawRectangle((j * tileSize) + (tileBuffer[1] * tileSize) + centerOffset[0],
						(i * tileSize) + (tileBuffer[0] * tileSize) + centerOffset[1], tileSize, tileSize);

					// Standard Pellet
					ofSetColor(ofColor(255, 255, 0));
					ofDrawCircle(((j + 0.5) * tileSize) + (tileBuffer[1] * tileSize) + centerOffset[0],
						((i + 0.5) * tileSize) + (tileBuffer[0] * tileSize) + centerOffset[1], tileSize / 8);
				}
				else if (currentBoard[i][j].isPowerPellet()) {
					// Tile
					ofSetColor(ofColor(0, 0, 0));
					ofDrawRectangle((j * tileSize) + (tileBuffer[1] * tileSize) + centerOffset[0],
						(i * tileSize) + (tileBuffer[0] * tileSize) + centerOffset[1], tileSize, tileSize);

					// Power Pellet
					ofSetColor(ofColor(255, 255, 0));
					ofDrawCircle(((j + 0.5) * tileSize) + (tileBuffer[1] * tileSize) + centerOffset[0],
						((i + 0.5) * tileSize) + (tileBuffer[0] * tileSize) + centerOffset[1], tileSize / 2.5);
				}
				else {
					// Tile
					ofSetColor(ofColor(0, 0, 0));
					ofDrawRectangle((j * tileSize) + (tileBuffer[1] * tileSize) + centerOffset[0],
						(i * tileSize) + (tileBuffer[0] * tileSize) + centerOffset[1], tileSize, tileSize);

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
	// currentScore
	string currentScore = std::to_string(pacman.getScore());

	// highScore
	string highScore;
	if (pacman.getScore() > highScores[0]) {
		highScore = std::to_string(pacman.getScore());
	}
	else {
		highScore = std::to_string(highScores[0]);
	}

	// Draw Upper Buffer
	ofSetColor(ofColor(0, 0, 0));
	ofDrawRectangle((tileBuffer[1] * tileSize) + centerOffset[0], centerOffset[1], currentBoard[0].size() * tileSize, tileBuffer[0] * tileSize);

	// Draw Upper Info
	ofSetColor(ofColor(255, 255, 255));
	emulogic.drawString("HIGH SCORE",
		((currentBoard[0].size() * tileSize) - emulogic.stringWidth("HIGH SCORE")) / 2 + (tileBuffer[1] * tileSize) + centerOffset[0], // Centered With Respect To The Board
		tileSize + centerOffset[1]); // Vertical tileBuffer Tile Zero
	emulogic.drawString(highScore,
		((currentBoard[0].size() * tileSize) - emulogic.stringWidth(highScore)) / 2 + (tileBuffer[1] * tileSize) + centerOffset[0], // Centered With Respect To The Board
		(tileSize * 2) + centerOffset[1]); // Vertical tileBuffer Tile One

	emulogic.drawString("1UP",
		((((currentBoard[0].size() * tileSize) - emulogic.stringWidth("HIGH SCORE")) / 2) - emulogic.stringWidth("1UP")) / 2 + (tileBuffer[1] * tileSize) + centerOffset[0], // Center Of: Left Board Edge & Left Edge Of 'HIGH SCORE'
		tileSize + centerOffset[1]); // Vertical tlleBuffer Tile Zero
	emulogic.drawString(currentScore,
		((((currentBoard[0].size() * tileSize) - emulogic.stringWidth("HIGH SCORE")) / 2) - emulogic.stringWidth("1UP")) / 2 + emulogic.stringWidth("1UP") - emulogic.stringWidth(currentScore) + (tileBuffer[1] * tileSize) + centerOffset[0], // Right Edge Of Score Lines Up With Right Edge Of '1UP'
		(tileSize * 2) + centerOffset[1]); // Vertical tileBuffer Tile One

	// Draw Left Buffer
	ofSetColor(ofColor(0, 0, 0));
	ofDrawRectangle(centerOffset[0],
		(tileBuffer[0] * tileSize) + centerOffset[1],
		tileBuffer[1] * tileSize, currentBoard.size() * tileSize);

	// Draw Lower Buffer
	ofSetColor(ofColor(0, 0, 0));
	ofDrawRectangle((tileBuffer[1] * tileSize) + centerOffset[0],
		(tileBuffer[0] * tileSize) + (currentBoard.size() * tileSize) + centerOffset[1],
		currentBoard[0].size() * tileSize, tileBuffer[2] * tileSize);

	// Draw Lower Info (Lives)
	ofSetColor(ofColor(255, 255, 255));
	vector<int> tilePosition{ (int)currentBoard.size() + 1, 3 };
	for (int i = 0; i < pacman.getLives() - 1; i++) {
		ofSetColor(ofColor(255, 255, 0));
		ofDrawCircle(((tilePosition[1] + (i * 2)) * tileSize) + centerOffset[0],
			(tilePosition[0] * tileSize) + (tileBuffer[0] * tileSize) + centerOffset[1],
			tileSize);
	}

	// Draw Right Buffer
	ofSetColor(ofColor(0, 0, 0));
	ofDrawRectangle((tileBuffer[1] * tileSize) + (currentBoard[0].size() * tileSize) + centerOffset[0],
		(tileBuffer[0] * tileSize) + centerOffset[1],
		tileBuffer[2] * tileSize,
		currentBoard.size() * tileSize);
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
	pacmanPath.arc(pacman.getCenterPixelPosition()[0] + (tileBuffer[1] * tileSize) + centerOffset[0],
		pacman.getCenterPixelPosition()[1] + (tileBuffer[0] * tileSize) + centerOffset[1],
		tileSize / 2, tileSize / 2,
		angleDisplacement + pacmanDegree, angleDisplacement - pacmanDegree);
	pacmanPath.draw();
}

void ofApp::drawGhosts() {
	/*
	// Draw targetTile
	for (Ghost *g : ghostsVector) {
		ofColor darkenedColor = g->getDefaultColor();
		darkenedColor.setBrightness(128);
		ofSetColor(darkenedColor);
		ofDrawRectangle(g->getTargetTilePixelPosition()[0] - (tileSize / 4) + centerOffset[0] ,
			g->getTargetTilePixelPosition()[1] - (tileSize / 4) + (buffer[0] * tileSize) + centerOffset[1],
			tileSize / 2, tileSize / 2);
	}
	*/

	for (Ghost *g : ghostsVector) {
		if (g->isEdible()) {
			if (frightenedTimer.count<std::chrono::seconds>() < 0.75 * frightenedTimeMarker) {
				g->flipWhichEdibleImage(true);
			}
			else {
				if (frightenedTimer.count<std::chrono::milliseconds>() / 250 % 2) {
					g->flipWhichEdibleImage(false);
				}
				else {
					g->flipWhichEdibleImage(true);
				}
			}
		}
		ofSetColor(ofColor(255, 255, 255));
		g->getImage().draw(g->getTopLeftPixelPosition()[0] + (tileBuffer[1] * tileSize) + centerOffset[0],
			g->getTopLeftPixelPosition()[1] + (tileBuffer[0] * tileSize) + centerOffset[1],
			tileSize, tileSize);
	}
}

void ofApp::drawGameOver() {
	// Buttons
	continueButton.setPosition((tileBuffer[1] * tileSize) + centerOffset[0],
		(currentBoard.size() * tileSize) + (tileBuffer[0] * tileSize) + centerOffset[1]);
	continueButton.setVisible(true);
	continueButton.draw();
}

void ofApp::drawHighScores() {
	ofBackground(ofColor(0, 0, 0));

	ofSetColor(ofColor(255, 255, 255));

	// Draw "HIGH SCORES"
	string str = "HIGH SCORES";
	emulogic.drawString(str,
		(screenWidth - emulogic.stringWidth(str)) / 2,
		((screenHeight - ((highScores.size() + 1) * emulogic.stringHeight(str))) / 2) + tileSize);

	// Draw Scores
	int count = 1;
	for (int score : highScores) {
		str = std::to_string(score);

		emulogic.drawString(str,
			(screenWidth - emulogic.stringWidth(str)) / 2,
			((screenHeight - ((highScores.size() + 1) * emulogic.stringHeight(str))) / 2) + tileSize + (count * tileSize));
		count++;
	}

	// Buttons
	continueButton.setPosition((tileBuffer[1] * tileSize) + centerOffset[0],
		(currentBoard.size() * tileSize) + (tileBuffer[0] * tileSize) + centerOffset[1]);
	continueButton.setVisible(true);
	continueButton.draw();
}

void ofApp::resetSprites() {
	// Reset drawPacman Variables
	angleDisplacement = 0;
	pacmanDegree = 0;

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
	// Reset Board
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

	// Set Level To 0
	level = 0;

	// Set Flags
	highScoreFlag = true;

	// Reset Board
	currentBoard = board->resetBoard();

	// Reset Sprites
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