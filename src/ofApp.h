#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "ofMain.h"
#include "ofxGui.h"

#include "ofEvents.h"
#include "button.h"
#include "RoundedButton.h"

#include "enums.h"
#include "cxxTimer.h"

#include "board.h"
#include "tile.h"

#include "pacman.h"

#include "ghost.h"
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
		void mousePressed(int x, int y, int button);
		void mouseDragged(int x, int y, int button);
		void keyPressed(int key);
		void windowResized(int w, int h);

		// Event Listeners
		void singlePlayerButtonListener(ofVec2f &e);
		void multiPlayerButtonListener(ofVec2f &e);
		void continueButtonListener(ofVec2f &e);

		// BoardEditor Listeners
		void editorDisplayBlockButtonListener();
		void editorWallBlockButtonListener();
		void editorStandardPelletBlockButtonListener();
		void editorPowerPelletBlockButtonListener();

		void editorPacmanSpriteButtonListener();

		void editorBlinkySpriteButtonListener();
		void editorBlinkyHomeTileButtonListener();

		void editorPinkySpriteButtonListener();
		void editorPinkyHomeTileButtonListener();

		void editorInkySpriteButtonListener();
		void editorInkyHomeTileButtonListener();

		void editorClydeSpriteButtonListener();
		void editorClydeHomeTileButtonListener();

		void editorContinueLabelListener() { std::cout << "Continue Pressed" << std::endl;  };

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
		const string port = "COM5";
		const int baudRate = 9600;
		ofSerial serial;
		string serialMessage = "";
		bool incomingMessage = false;

		// OfxGui
		EditorOptions currentEditorOption = DISPLAY_BLOCK;
		ofxPanel levelEditorPanel;

		ofxButton editorDisplayBlockButton;
		ofxButton editorWallBlockButton;
		ofxButton editorStandardPelletBlockButton;
		ofxButton editorPowerPelletBlockButton;

		ofxButton editorPacmanSpriteButton;

		ofxButton editorBlinkySpriteButton;
		ofxButton editorBlinkyHomeTileButton;

		ofxButton editorPinkySpriteButton;
		ofxButton editorPinkyHomeTileButton;

		ofxButton editorInkySpriteButton;
		ofxButton editorInkyHomeTileButton;

		ofxButton editorClydeSpriteButton;
		ofxButton editorClydeHomeTileButton;
		
		// Buttons
		RoundedButton singlePlayerButton;
		RoundedButton multiPlayerButton;

		Button continueButton;

		// Timers
		const vector<SpriteMode> modeMarkers{ SCATTER, CHASE, SCATTER, CHASE, SCATTER, CHASE, SCATTER, CHASE };
		const vector<float> modeTimeMarkers{ 7, 20, 7, 20, 5, 20, 5, std::numeric_limits<float>::infinity() };

		Timer modeTimer;
		int modeIndex = 0;

		const int frightenedTimeMarker = 7;
		Timer frightenedTimer;

		// Flags
		bool redrawBackgroundFlag = false;
		bool highScoreFlag = true;

		// Game Variables
		vector<int> highScores{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

		BoardGenerator *board = new BoardGenerator();
		vector<vector<Tile>> currentBoard = board->resetBoard();
		Pacman &pacman = Pacman(&currentBoard);
		Ghost &blinky = Blinky(&currentBoard, &pacman);
		Ghost &pinky = Pinky(&currentBoard, &pacman);
		Ghost &inky = Inky(&currentBoard, &pacman, &blinky);
		Ghost &clyde = Clyde(&currentBoard, &pacman);
		vector<Ghost*> ghostsVector = vector<Ghost*>{&blinky, &pinky, &inky, &clyde };

		int level = 0;

		// drawPacMan Variables
		int angleDisplacement = 0;
		
		const int maxDegree = 60;
		int pacmanDegree = 0;

		const int cyclesPerSecond = 5;
		const int degreeIncrement = (2 * cyclesPerSecond) * (maxDegree / frameRate);
		bool degreeFlag = true;

		// Helper Methods For Display Render
		void drawLandingPage();
		void drawLevelEditor();
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