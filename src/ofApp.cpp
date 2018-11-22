#include "ofApp.h"

/* Private Methods */
// Helper Methods For Display Render
void ofApp::drawLandingPage() {
	ofSetColor(255, 255, 100);

	// "PACMAN" Horizontally And Vertically Centered With Respect To The Screen
	crackman.drawString("PAC-MAN",
		(screenWidth - crackman.stringWidth("PAC-MAN")) / 2,
		(screenHeight - crackman.stringHeight("PAC-MAN")) / 2);
}

void ofApp::drawInstructions() {

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
					ofSetColor(255, 255, 100);
					ofDrawCircle((j + 0.5) * tileSize + centerOffset[0], (i + 0.5) * tileSize + centerOffset[1], tileSize / 8);
				}
				else if (board[i][j].isPowerPellet()) {
					// Tile
					ofSetColor(0, 0, 0);
					ofDrawRectangle(j * tileSize + centerOffset[0], i * tileSize + centerOffset[1], tileSize, tileSize);

					// Power Pellet
					ofSetColor(255, 255, 100);
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

	// Retrieve currentScore
	string currentScore = std::to_string(pacman.getScore());

	// "HIGH SCORE" Horizontally Centered With Respect To The Screen
	vector<int> highScoreLabelTilePosition = { 1, (int)((board[0].size() - string("HIGH SCORE").length()) / 2) };

	// "1UP" Horizontally Centered With Respect To "HIGH SCORE"
	vector<int> playerLabelTilePosition = { 1, (int)((highScoreLabelTilePosition[1] - string("1UP").length()) / 2) };

	// "Rightermost Entry Of Score Is One Tile After End Of "1UP"
	vector<int> currentScoreTilePosition = { 2, (int)(playerLabelTilePosition[1] + string("1UP").length() + 1 - currentScore.length()) };

	// Draw
	emulogic.drawString("1UP",
		playerLabelTilePosition[1] * tileSize + centerOffset[0],
		playerLabelTilePosition[0] * tileSize + centerOffset[1]);
	emulogic.drawString("HIGH SCORE",
		highScoreLabelTilePosition[1] * tileSize + centerOffset[0],
		highScoreLabelTilePosition[0] * tileSize + centerOffset[1]);
	emulogic.drawString(currentScore,
		currentScoreTilePosition[1] * tileSize + centerOffset[0],
		currentScoreTilePosition[0] * tileSize + centerOffset[1]);

	// Lives
	vector<int> tilePosition{ (int)board.size() - 1, 3 };
	for (int i = 0; i < pacman.getLives() - 1; i++) {
		ofSetColor(255, 255, 255);
		ofDrawCircle((tilePosition[1] + i * 2) * tileSize + centerOffset[0],
			(tilePosition[0]) * tileSize + centerOffset[1],
			tileSize);
	}
}

void ofApp::drawPacMan() {
	ofSetColor(255, 255, 100);
	ofDrawCircle(pacman.getPixelPosition()[0] + centerOffset[0], pacman.getPixelPosition()[1] + centerOffset[1], tileSize / 2);
}

void ofApp::drawGhosts() {
	ofSetColor(255, 0, 0);
	ofDrawCircle(blinky.getPixelPosition()[0] + centerOffset[0], blinky.getPixelPosition()[1] + centerOffset[1], tileSize / 2);
	//ofDrawRectangle(blinky.getTargetTilePixelPosition()[0] + centerOffset[0] - tileSize / 4, 
	//				blinky.getTargetTilePixelPosition()[1] + centerOffset[1] - tileSize / 4,
	//				tileSize / 2, tileSize / 2);

	ofSetColor(255, 185, 255);
	ofDrawCircle(pinky.getPixelPosition()[0] + centerOffset[0], pinky.getPixelPosition()[1] + centerOffset[1], tileSize / 2);
	//ofDrawRectangle(pinky.getTargetTilePixelPosition()[0] + centerOffset[0] - tileSize / 4,
	//				pinky.getTargetTilePixelPosition()[1] + centerOffset[1] - tileSize / 4,
	//				tileSize / 2, tileSize / 2);

	ofSetColor(0, 255, 255);
	ofDrawCircle(inky.getPixelPosition()[0] + centerOffset[0], inky.getPixelPosition()[1] + centerOffset[1], tileSize / 2);
	//ofDrawRectangle(inky.getTargetTilePixelPosition()[0] + centerOffset[0] - tileSize / 4,
	//				inky.getTargetTilePixelPosition()[1] + centerOffset[1] - tileSize / 4,
	//				tileSize / 2, tileSize / 2);

	ofSetColor(255, 185, 80);
	ofDrawCircle(clyde.getPixelPosition()[0] + centerOffset[0], clyde.getPixelPosition()[1] + centerOffset[1], tileSize / 2);
	//ofDrawRectangle(clyde.getTargetTilePixelPosition()[0] + centerOffset[0] - tileSize / 4,
	//				clyde.getTargetTilePixelPosition()[1] + centerOffset[1] - tileSize / 4,
	//				tileSize / 2, tileSize / 2);
}

void ofApp::drawGameOver() {

}

void ofApp::drawHighScores() {

}

// Reset Functions
void ofApp::resetSprites() {
	// Reset Sprites
	pacman.resetLevel(level);
	blinky.resetLevel(level);
	pinky.resetLevel(level);
	inky.resetLevel(level);
	clyde.resetLevel(level);

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
	// Create A New Board
	board = Board().getBoard();

	// Set Level To 0
	level = 0;

	// Set Flags
	highScoreFlag = true;

	// Reset Game
	pacman.resetGame();
	blinky.resetGame();
	pinky.resetGame();
	inky.resetGame();
	clyde.resetGame();

	// Set GameState
	currentState = PAUSED;
}

/* Public Methods */
// Setup Method
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

// Update Game Information
void ofApp::update() {
	if (currentState == IN_PROGRESS) {
		// Update Sprites
		pacman.update(board);
		blinky.update(board, pacman);
		pinky.update(board, pacman);
		inky.update(board, pacman, blinky);
		clyde.update(board, pacman);

		// Check For Pacman - Ghost Collision
		if (pacman.getTilePosition() == blinky.getTilePosition() ||
			pacman.getTilePosition() == pinky.getTilePosition() ||
			pacman.getTilePosition() == inky.getTilePosition() ||
			pacman.getTilePosition() == clyde.getTilePosition()) {
			// Decrement Lives
			pacman.decrementLives();

			// Reset Sprites
			resetSprites();
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
				std::cerr << "Unable To Open File" << std::endl;
				std::exit(1);
			}

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
				std::cerr << "Unable To Open File" << std::endl;
				std::exit(1);
			}

			// Change Flag
			highScoreFlag = false;
		}
	}
}

// Draw Game
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

// Action Handlers
/*
	F12		->	toggle fullscreen
	P		->	toggle pause
	WASD	->	directional control
*/
void ofApp::keyPressed(int key) {
	// TODO: Remove
	if (key == OF_KEY_CONTROL) {
		// Flip State
		if (currentState = START) {
			currentState = INSTRUCTIONS;
		}
		else if (currentState = INSTRUCTIONS) {
			vector<int> rowBuffer{ 3, 2 };
			// Set Sprite's homeTilePosition
			blinky.setHomeTilePosition(vector<int>{ 1 + rowBuffer[1], 1 });
			pinky.setHomeTilePosition(vector<int>{ (((int)board.size() - 1) - 1) - rowBuffer[1], ((int)board.size() - 1) - 1 });
			inky.setHomeTilePosition(vector<int>{ 1 + rowBuffer[1], ((int)board.size() - 1) - 1});
			clyde.setHomeTilePosition(vector<int>{ (((int)board.size() - 1) - 1) - rowBuffer[1], 1 });

			// Set Sprite's initialTilePosition
			pacman.setInitialPosition(vector<int>{ 26, 14 });
			blinky.setInitialTilePosition(vector<int>{ 4, 1 });
			pinky.setInitialTilePosition(vector<int>{ 32, 26});
			inky.setInitialTilePosition(vector<int>{ 4, 26 });
			clyde.setInitialTilePosition(vector<int>{ 32, 1 });

			// Reset Game
			resetGame();
		}
	}
	else if (key == OF_KEY_ALT) {
		blinky.reverseDirection();
		inky.reverseDirection();
		pinky.reverseDirection();
		clyde.reverseDirection();
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
	blinky.resize(screenWidth, screenHeight, tileSize);
	pinky.resize(screenWidth, screenHeight, tileSize);
	inky.resize(screenWidth, screenHeight, tileSize);
	clyde.resize(screenWidth, screenHeight, tileSize);

}