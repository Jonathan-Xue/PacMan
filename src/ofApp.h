#pragma once

#include "ofMain.h"

enum GameState {
	START,
	INSTRUCTIONS,
	IN_PROGRESS,
	PAUSED,
	FINISHED
};

class ofApp : public ofBaseApp{

	private: 
		// Variables
		ofSoundPlayer background_music_;
		GameState current_state_;

		int screen_width_ = 1024;
		int screen_height_ = 768;
		int frame_rate_ = 60;

		// Helper Methods For Display Render
		// GameState = START
		void drawLandingPage();

		// GameState = INSTRUCTIONS
		void drawInstructions();

		// GameState = IN_PROGRESS || PAUSED
		void drawGameBoard();
		void drawMisc();
		void drawPacMan();
		void drawGhosts();

		// GameState = FINISHED
		void drawHighScores();

		// String Bounding Box
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
