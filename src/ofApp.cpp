#include "ofApp.h"

/* Private Methods */
// Helper Methods For Display Render
void ofApp::drawLandingPage() {

}

void ofApp::drawInstructions() {

}

void ofApp::drawGameBoard() {
	for (size_t i = 0; i < board.size(); i++) {
		for (size_t j = 0; j < board[0].size(); j++) {
			if (board[i][j].getID() == -1) {
				// Invalid Block
				ofSetColor(0, 0, 0);
				ofDrawRectangle(tileSize * j + centerOffset[0], tileSize * i + centerOffset[1], tileSize, tileSize);
			}
			else if (board[i][j].getID() == 0) {
				// Wall
				ofSetColor(50, 50, 255);
				ofDrawRectangle(tileSize * j + centerOffset[0], tileSize * i + centerOffset[1], tileSize, tileSize);
			} 
			else if (board[i][j].getID() == 1) {
				if (board[i][j].isStandardPellet()) {
					// Standard Pellet
					ofSetColor(255, 255, 100);
					ofDrawRectangle(tileSize * j + centerOffset[0], tileSize * i + centerOffset[1], tileSize, tileSize);
				}
				else if (board[i][j].isPowerPellet()) {
					// Power Pellet
					ofSetColor(255, 150, 100);
					ofDrawRectangle(tileSize * j + centerOffset[0], tileSize * i + centerOffset[1], tileSize, tileSize);
				}
				else {
					// No Pellet
					ofSetColor(100, 100, 150);
					ofDrawRectangle(tileSize * j + centerOffset[0], tileSize * i + centerOffset[1], tileSize, tileSize);
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

}

void ofApp::drawPacMan() {
	ofSetColor(255, 255, 255);
	ofDrawCircle(pacman.getPixelPosition()[0] + centerOffset[0], pacman.getPixelPosition()[1] + centerOffset[1], tileSize / 2);
}

void ofApp::drawGhosts() {
	ofSetColor(255, 0, 0);
	ofDrawCircle(blinky.getPixelPosition()[0] + centerOffset[0], blinky.getPixelPosition()[1] + centerOffset[1], tileSize / 2);	

	ofSetColor(255, 185, 255);
	ofDrawCircle(pinky.getPixelPosition()[0] + centerOffset[0], pinky.getPixelPosition()[1] + centerOffset[1], tileSize / 2);

	ofSetColor(0, 255, 255);
	ofDrawCircle(inky.getPixelPosition()[0] + centerOffset[0], inky.getPixelPosition()[1] + centerOffset[1], tileSize / 2);

	ofSetColor(255, 185, 80);
	ofDrawCircle(clyde.getPixelPosition()[0] + centerOffset[0], clyde.getPixelPosition()[1] + centerOffset[1], tileSize / 2);
}

void ofApp::drawGameOver() {

}

void ofApp::drawHighScores() {

}

ofRectangle ofApp::getBitmapStringBoundingBox(string text) {
	vector<string> lines = ofSplitString(text, "\n");
	int maxLineLength = 0;

	for (int i = 0; i < (int)lines.size(); i++) {
		const string & line(lines[i]);
		int currentLineLength = 0;

		for (int j = 0; j < (int)line.size(); j++) {
			if (line[j] == '\t') {
				currentLineLength += 8 - (currentLineLength % 8);
			}
			else {
				currentLineLength++;
			}
		}

		maxLineLength = MAX(maxLineLength, currentLineLength);
	}

	int padding = 4;
	int fontSize = 8;
	float leading = 1.7;
	int height = lines.size() * fontSize * leading - 1;
	int width = maxLineLength * fontSize;

	return ofRectangle(0, 0, width, height);
}

// Reset
void ofApp::reset() {

}

/* Public Methods */
// Setup Method
void ofApp::setup(){
	// Set Window Name
	ofSetWindowTitle("Pac-Man");

	// Background Color
	ofBackground(0, 255, 0);
	ofSetBackgroundAuto(false);

	// Background Music
	backgroundMusic.load("temp.mp3");
	backgroundMusic.setLoop(true);
	// backgroundMusic.play();

	// Create A New Board
	board = Board().getBoard();

	// Set GameState
	currentState = IN_PROGRESS;

	// Resize
	windowResized(screenWidth, screenHeight);
}

// Update Game Information
void ofApp::update(){
	if (currentState == IN_PROGRESS) {
		pacman.update(board);
		blinky.update(board, pacman);
		pinky.update(board, pacman);
		inky.update(board, pacman, blinky);
		clyde.update(board, pacman);
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
void ofApp::keyPressed(int key){
	if (key == OF_KEY_F12) {
		ofToggleFullscreen();
		return;
	}

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

void ofApp::mousePressed(int x, int y, int button){

}

void ofApp::windowResized(int w, int h){
	// Update Width & Height
	screenWidth = w;
	screenHeight = h;

	// Tile Size
	tileSize = min(screenHeight / board.size(), screenWidth / board[0].size());

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