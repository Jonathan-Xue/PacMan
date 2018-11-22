#pragma once

#include "enums.h"

#include "tile.h"
#include "pacman.h"

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
		// Constructors
		Ghost();
		~Ghost();

		// Methods
		void update(vector<vector<Tile>> board, Pacman pacman);

		void calculateTargetTile(Pacman pacman);

		void updateVelocity(vector<vector<Tile>> board);
		bool checkValidVelocity(vector<vector<Tile>> board, vector<int> velocity);
		double calculateDistance(double x1, double y1, double x2, double y2);

		void move();

		void adjustBounds(vector<vector<Tile>> board);

		// Reset Functions
		void resetLevel(int l);
		void resetGame();

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

		// Resize
		void resize(int w, int h, int ts);

};