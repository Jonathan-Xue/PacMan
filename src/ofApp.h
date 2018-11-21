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
		const int frameRate = 60;

		ofSoundPlayer backgroundMusic;
		GameState currentState;

		ofTrueTypeFont crackman;
		ofTrueTypeFont emulogic;

		int screenWidth = ofGetWindowWidth();
		int screenHeight = ofGetWindowHeight();
		int tileSize;

		vector<int> centerOffset{ 0, 0 };

		// Game Variables
		vector<int> highScores{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

		vector<vector<Tile>> board = Board().getBoard();
		Pacman pacman;
		Blinky blinky;
		Clyde clyde;
		Inky inky;
		Pinky pinky;

		int level = 0;

		// Flags
		bool highScoreFlag = true;

		// Helper Methods For Display Render
		void drawLandingPage();
		void drawInstructions();
		void drawGameBoard();
		void drawMisc();
		void drawPacMan();
		void drawGhosts();
		void drawGameOver();
		void drawHighScores();

		// Reset Functions
		void resetSprites();
		void resetLevel();
		void resetGame();

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