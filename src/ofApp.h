#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "ofMain.h"

#include "board.h"
#include "tile.h"

#include "pacman.h"

#include "blinky.h"
#include "clyde.h"
#include "inky.h"
#include "pinky.h"

using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;

enum GameState {
	START,
	INSTRUCTIONS,
	IN_PROGRESS,
	PAUSED,
	GAME_OVER,
	HIGH_SCORE
};

class ofApp : public ofBaseApp {

	private: 
		// OpenFramework Variables
		ofSoundPlayer backgroundMusic;
		GameState currentState;

		int screenWidth = ofGetWindowWidth();
		int screenHeight = ofGetWindowHeight();
		int frameRate = 60;
		int tileSize;

		// Game Variables
		vector<vector<Tile>> board;
		Pacman pacman;
		Blinky blinky;
		Clyde clyde;
		Inky inky;
		Pinky pinky;

		// Helper Methods For Display Render
		void drawLandingPage();
		void drawInstructions();
		void drawGameBoard();
		void drawMisc();
		void drawPacMan();
		void drawGhosts();
		void drawGameOver();
		void drawHighScores();

		/*
			Purpose: Return String Bounding Box
			Author: roymacdonald
			Date: February, 2016
			Link: https://forum.openframeworks.cc/t/how-to-get-size-of-ofdrawbitmapstring/22578/7
		*/
		ofRectangle getBitmapStringBoundingBox(string text);

		// Reset
		void reset();

	public:
		// Setup
		void setup();

		// Game Loop
		void update();
		void draw();

		// User Actions
		void keyPressed(int key);
		void mousePressed(int x, int y, int button);
		void windowResized(int w, int h);	

};