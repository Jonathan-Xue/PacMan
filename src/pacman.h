#pragma once

#include "enums.h"

#include "tile.h"

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

class Pacman {

	public:
		// Default Constructor
		Pacman();

		// Transfer Constructor
		Pacman(const Pacman& other) = default;

		// Copy Constructor
		Pacman(Pacman&& other) = default;

		// Destructor
		~Pacman();

		// Copy Assignment Operator
		Pacman& operator=(const Pacman& other) = default;

		// Transfer Assignment Operator
		Pacman& operator=(Pacman&& other) = default;

		/*
			Update
				@param: board
		*/
		void update(vector<vector<Tile>> &board);

		/*
			Eat Pellets
				@param: board
		*/
		void eat(vector<vector<Tile>> &board);

		/*
			Update Velocity
				@param: board
		*/
		void updateVelocity(vector<vector<Tile>> board);

		/*
			Update Velocity
				@param: board
				@param: velocity
				@return: Boolean Detailing If The Input Velocity Is Valid
		*/
		bool checkValidVelocity(vector<vector<Tile>> board, vector<int> velocity);

		/*
			Move Pacman In The Direction Of CurrentVelocity
		*/
		void move();

		/*
			Wraparound The Board
				@param: board
		*/
		void adjustBounds(vector<vector<Tile>> board);

		// Reset Functions
		void resetLevel(int l);
		void resetGame();

		/*
			Adjust The Sprite Size
				@param: w
					The width of the window
				@param: h
					The height of the window
				@param: ts
					The width/height of each tile on the board
		*/
		void resize(int w, int h, int ts);

		// Getters
		int getLives();
		int getScore();

		vector<double> getPixelPosition();
		vector<int> getTilePosition();
		vector<int> getCurrentVelocity();

		// Setters
		void setMode(SpriteMode m);
		void decrementLives();
		void setInitialPosition(vector<int> itp);
		void setQueuedVelocity(vector<int> v);

	private:
		// OpenFramework Variables
		const int frameRate = 60;
		const double epsilon = 0.001;

		int screenWidth;
		int screenHeight;
		int tileSize;

		// Enums
		SpriteMode mode = CHASE;

		// Flags
		vector<bool> skipFrames = { false, false, false };

		// Class Variables
		const int maxLives = 3;
		int level = 0;
		int lives = 0;
		int score = 0;

		vector<int> initialTilePosition = { 0, 0 };
		vector<int> tilePosition = { 0, 0 };
		vector<double> pixelPosition = { 0, 0 };

		vector<int> currentVelocity = { 0, 0 };
		vector<int> queuedVelocity = { 0, 0 };

		// Separate Each Tile Into X Ticks
		double maxTick = 100.0;
		vector<double> currentTick = { maxTick / 2, maxTick / 2 };

		// Tiles Per Second
		double maxTilesPerSecond = 10;
		double tilesPerSecond = 8;

		// Ticks Per Frame
		double speed = 0.0;

};