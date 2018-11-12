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

			}
			else if (board[i][j].getID() == 0) {
				// Wall

			} 
			else if (board[i][j].getID() == 1) {
				if (board[i][j].isStandardPellet()) {
					// Standard Pellet

				}
				else if (board[i][j].isPowerPellet()) {
					// Power Pellet

				}
				else {
					// No Pellet

				}
			}
			else {
				std::cerr << "Error. GameBoard Is Invalid" << std::endl;
				std::exit(1);
			}
		}
	}
}

void ofApp::drawMisc() {

}

void ofApp::drawPacMan() {

}

void ofApp::drawGhosts() {

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

	// Background Music
	backgroundMusic.load("temp.mp3");
	backgroundMusic.setLoop(true);
	backgroundMusic.play();

	// Create A New Board
	board = Board().getBoard();

	// Set GameState
	currentState = IN_PROGRESS;
}

// Update Game Information
void ofApp::update(){
	if (currentState != PAUSED) {
		
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

		}
		else if (upper_key == 'A') {

		}
		else if (upper_key == 'S') {

		}
		else if (upper_key == 'D') {

		}
	}
}

void ofApp::mousePressed(int x, int y, int button){

}

void ofApp::windowResized(int w, int h){
	screenWidth = w;
	screenHeight = h;
}