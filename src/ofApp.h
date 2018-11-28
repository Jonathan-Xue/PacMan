#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "ofMain.h"

#include "enums.h"
#include "cxxTimer.h"

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

class ofApp : public ofBaseApp {

	public:
		// Setup
		void setup();
		void setupSerial();

		// Game Loop
		void update();
		void draw();

		// User Actions
		/*
			F12->toggle fullscreen
			P->toggle pause
			WASD->directional control
		*/
		void keyPressed(int key);
		void mousePressed(int x, int y, int button);
		void windowResized(int w, int h);	

	private:
		// OpenFramework Variables
		const int frameRate = 60;

		ofSoundPlayer backgroundMusic;
		GameState currentState;

		ofTrueTypeFont crackman;
		ofTrueTypeFont emulogic;

		int screenWidth = ofGetWindowWidth();
		int screenHeight = ofGetWindowHeight();
		int tileSize = 0;

		vector<int> centerOffset{ 0, 0 };

		// OfSerial
		const string port = "COM4";
		const int baudRate = 9600;
		ofSerial serial;
		string serialMessage = "";
		bool incomingMessage = false;

		// Timers
		const vector<SpriteMode> modeMarkers{ SCATTER, CHASE, SCATTER, CHASE, SCATTER, CHASE, SCATTER, CHASE };
		const vector<float> modeTimeMarkers{ 7, 20, 7, 20, 5, 20, 5, std::numeric_limits<float>::infinity() };

		Timer modeTimer;
		int modeIndex = 0;

		const int frightenedTimeMarker = 7;
		Timer frightenedTimer;

		// Flags
		bool highScoreFlag = true;

		// Game Variables
		vector<int> highScores{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

		vector<vector<Tile>> board = Board().getBoard();
		Pacman &pacman = Pacman(&board);
		Ghost &blinky = Blinky(&board, &pacman);
		Ghost &pinky = Pinky(&board, &pacman);
		Ghost &inky = Inky(&board, &pacman, &blinky);
		Ghost &clyde = Clyde(&board, &pacman);
		vector<Ghost*> ghostsVector = vector<Ghost*>{&blinky, &pinky, &inky, &clyde };

		int level = 0;

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

};