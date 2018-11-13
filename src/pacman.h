#pragma once

#include "tile.h"

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

class Pacman {

	private:
		// OpenFramework Variables
		int screenWidth;
		int screenHeight;
		int tileSize;

		// Class Variables
		vector<int> tilePosition;
		vector<double> pixelPosition;

		vector<int> currentVelocity;
		vector<int> queuedVelocity;
		
		// Separate Each Tile Into X Ticks
		double maxTick = 100.0;
		vector<double> currentTick = { maxTick / 2, maxTick / 2 };

		// Tiles Per Second
		int tilesPerSecond;

		// Speed (Ticks Per Frame)
		double speed;
		

	public:
		// Constructors
		Pacman();
		~Pacman();

		// Methods
		void move(vector<vector<Tile>> &board);
		void calculatePixelPosition();
		void adjustBounds(vector<vector<Tile>> &board);
		bool checkValidVelocity(vector<vector<Tile>> &board, vector<int> velocity);

		// Setter
		void setQueuedVelocity(vector<int> v);

		// Getters
		vector<double> getPixelPosition();
		vector<int> getTilePosition();

		// Resize
		void resize(int w, int h, int ts);

};