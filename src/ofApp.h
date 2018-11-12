#pragma once

#include "ofMain.h"

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

		// GameState = GAME_OVER
		void drawGameOver();

		// GameState = HIGH_SCORE
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