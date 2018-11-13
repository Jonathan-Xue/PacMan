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
		const double epsilon = 0.001;
		int screenWidth;
		int screenHeight;
		int tileSize;

		// Class Variables
		vector<int> tilePosition;
		vector<double> pixelPosition;

		vector<int> currentVelocity;
		vector<int> queuedVelocity;
		
		// Separate Each Tile Into X Ticks
		const double maxTick = 100.0;
		vector<double> currentTick = { maxTick / 2, maxTick / 2 };

		// Tiles Per Second
		const int tilesPerSecond = 10;

		// Ticks Per Frame
		double speed;

	public:
		// Constructors
		Pacman();
		~Pacman();

		// Methods
		void move(vector<vector<Tile>> &board);
		bool checkValidVelocity(vector<vector<Tile>> &board, vector<int> velocity); 
		void adjustBounds(vector<vector<Tile>> &board);
		void calculatePixelPosition();

		// Setter
		void setQueuedVelocity(vector<int> v);

		// Getters
		vector<double> getPixelPosition();
		vector<int> getTilePosition();

		// Resize
		void resize(int w, int h, int ts);

};