#pragma once

#include "tile.h"

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

class Ghost {

	protected:
		// OpenFramework Variables
		const double epsilon = 0.001;
		int screenWidth;
		int screenHeight;
		int tileSize;

		// Class Variables
		vector<int> tilePosition = { 0, 0 };
		vector<double> pixelPosition = { 0, 0 };

		vector<int> targetTile = { 0, 0 };

		vector<int> currentVelocity = { 0, 0 };
		vector<int> queuedVelocity = { 0, 0 };

		// Separate Each Tile Into X Ticks
		const double maxTick = 100.0;
		vector<double> currentTick = { maxTick / 2, maxTick / 2 };

		// Tiles Per Second
		const int tilesPerSecond = 10;

		// Ticks Per Frame
		double speed = 0.0;

	public:
		// Constructors
		Ghost();
		~Ghost();

		// Methods
		void update(vector<vector<Tile>> &board);

		void updateVelocity(vector<vector<Tile>> board);
		bool checkValidVelocity(vector<vector<Tile>> board, vector<int> velocity);

		void move();

		void adjustBounds(vector<vector<Tile>> board);

		void calculatePixelPosition();

		// Getters
		vector<double> getPixelPosition();
		vector<int> getTilePosition();

		// Resize
		void resize(int w, int h, int ts);

};