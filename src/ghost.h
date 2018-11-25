#pragma once

#include "enums.h"

#include "tile.h"

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

class Ghost {

	protected:
		// OpenFramework Variables
		const int frameRate = 60;
		const double epsilon = 0.001;

		int screenWidth;
		int screenHeight;
		int tileSize;

		// Enums
		SpriteMode mode = SCATTER;

		// Flags
		bool queuedReverseDirectionFlag = false;
		bool reverseDirectionFlag = false;

		// Game Variables
		vector<vector<Tile>> *board;

		// Class Variables
		int level = 0;

		vector<int> homeTilePosition = { 0, 0 };
		vector<int> initialTilePosition = { 0, 0 };
		vector<int> tilePosition = { 0, 0 };
		vector<double> pixelPosition = { 0, 0 };

		vector<int> targetTile = { 0, 0};

		vector<int> currentVelocity = { 0, 0 };
		vector<vector<int>> queuedVelocity{ {0, -1}, {-1, 0}, {0, 1}, {1, 0} };

		// Separate Each Tile Into X Ticks
		double maxTick = 100.0;
		vector<double> currentTick = { maxTick / 2, maxTick / 2 };

		// Tiles Per Second
		double maxTilesPerSecond = 10;
		double tilesPerSecond = 7.5;

		// Ticks Per Frame
		double speed = 0.0;

	public:
		// Default
		Ghost();
		
		// Copy Constructor
		Ghost(const Ghost& other) = default;

		// Transfer Constructor
		Ghost(Ghost&& other) = default;

		// Destructor
		~Ghost();

		// Copy Assignment Operator
		Ghost& operator=(const Ghost& other) = default;

		// Transfer Assignment Operator
		Ghost& operator=(Ghost&& other) = default;

		/*
			Update
		*/
		void update();

		/*
			Set The targetTile
				Pure Virtual Class: Must Be Defined In Subclass/Child
		*/
		virtual void calculateTargetTile() = 0;

		/*
			Update Velocity
		*/
		void updateVelocity();

		/*
			Update Velocity
				@param: velocity
				@return: Boolean Detailing If The Input Velocity Is Valid
		*/
		bool checkValidVelocity(vector<int> velocity);

		/*
			Calculate Euclidean Distance
				@param: xi
				@param: yi
				@param: x2
				@param: y2
				@return: Euclidean Distance Between (x1, y1) and (x2, y2)
		*/
		double calculateDistance(double x1, double y1, double x2, double y2);

		/*
			Move Ghost In The Direction Of CurrentVelocity
		*/
		void move();

		/*
			Wraparound The Board
		*/
		void adjustBounds();

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
		vector<double> getPixelPosition();
		vector<int> getTilePosition();

		vector<double> getTargetTilePixelPosition();
		vector<int> getTargetTile();

		// Setters
		void reverseDirection();
		void setMode(SpriteMode m);
		void setHomeTilePosition(vector<int> htp);
		void setInitialTilePosition(vector<int> itp);

};