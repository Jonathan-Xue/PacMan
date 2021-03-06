#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "ofMain.h"
#include "ofxGui.h"

#include "ofEvents.h"
#include "gui/button.h"
#include "gui/roundedButton.h"
#include "gui/levelEditorPanel.h"

#include "enums.h"
#include "misc/timer.h"

#include "board/board.h"
#include "board/tile.h"

#include "sprites/pacman.h"
#include "sprites/ghost.h"

#include "sprites/ghosts/blinky.h"
#include "sprites/ghosts/clyde.h"
#include "sprites/ghosts/inky.h"
#include "sprites/ghosts/pinky.h"

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
	void mousePressed(ofMouseEventArgs &args);
	void mouseDragged(ofMouseEventArgs &args);
	void keyPressed(int key);
	void windowResized(int w, int h);

	// Event Listeners
	void singlePlayerButtonListener(ofVec2f &e);
	void continueButtonListener(ofVec2f &e);

private:
	const bool debug = false;

	// OpenFramework Variables
	const int frameRate = 60;

	ofSoundPlayer backgroundMusic;
	GameState currentState;

	ofTrueTypeFont crackman;
	ofTrueTypeFont emulogic;

	int screenWidth = ofGetWindowWidth();
	int screenHeight = ofGetWindowHeight();
	int tileSize = 0;

	// OfSerial
	const string port = "COM5";
	const int baudRate = 9600;
	ofSerial serial;
	string serialMessage = "";
	bool incomingMessage = false;

	// OfxGui
	EditorOptions currentEditorOption = WALL_BLOCK;
	LevelEditorPanel levelEditorPanel = LevelEditorPanel(&currentEditorOption);

	// Buttons
	RoundedButton singlePlayerButton;
	Button continueButton;

	// Timers
	const vector<SpriteMode> modeMarkers{ SCATTER, CHASE, SCATTER, CHASE, SCATTER, CHASE, SCATTER, CHASE };
	const vector<float> modeTimeMarkers{ 7, 20, 7, 20, 5, 20, 5, std::numeric_limits<float>::infinity() };

	Timer modeTimer;
	int modeIndex = 0;

	const int frightenedTimeMarker = 8;
	Timer frightenedTimer;

	// Flags
	bool redrawBackgroundFlag = false;
	bool highScoreFlag = true;

	// Game Variables
	vector<int> highScores{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	BoardGenerator *board = new BoardGenerator();
	vector<vector<Tile>> currentBoard = board->resetBoard();
	Pacman* pacman = new Pacman(&currentBoard);
	Ghost* blinky = new Blinky(&currentBoard, pacman);
	Ghost* pinky = new Pinky(&currentBoard, pacman);
	Ghost* inky = new Inky(&currentBoard, pacman, blinky);
	Ghost* clyde = new Clyde(&currentBoard, pacman);
	vector<Ghost*> ghostsVector = vector<Ghost*>{ blinky, pinky, inky, clyde };

	int level = 0;
	const int pointsPerGhost = 500;

	// drawPacman, drawGhosts, drawBoard, drawMisc, drawLevelEditor Variables
	vector<int> centerOffset{ 0, 0 };
	vector<int> tileBuffer = vector<int>{ 3, 1, 2, 1 };

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