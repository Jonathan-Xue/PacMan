#include "ofApp.h"

/* Private Methods */
// Helper Methods For Display Render
void ofApp::drawLandingPage() {

}

void ofApp::drawInstructions() {

}

void ofApp::drawGameBoard() {

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
	ofSetWindowTitle("Pac-Man");

	background_music_.load("temp.mp3");
	background_music_.setLoop(true);
	background_music_.play();
}

// Update Game Information
void ofApp::update(){
	if (current_state_ != PAUSED) {
		
	}
}

// Draw Game
void ofApp::draw() {
	switch (current_state_) {
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
		if (current_state_ == IN_PROGRESS) {
			current_state_ = PAUSED;
		}
		else if (current_state_ == PAUSED) {
			current_state_ = IN_PROGRESS;
		}
		return;
	}
	else if (current_state_ == IN_PROGRESS) {
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
	screen_width_ = w;
	screen_height_ = h;
}