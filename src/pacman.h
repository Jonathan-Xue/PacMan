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
		vector<int> pixelPosition;
		vector<int> tilePosition;

		vector<int> currentVelocity;
		vector<int> queuedVelocity;
		int tilesPerSecond;
		int speed;

	public:
		// Constructors
		Pacman();
		~Pacman();

		// Methods
		void calculateTilePosition();
		void move(vector<vector<Tile>> &board);
		bool checkValidVelocity(vector<vector<Tile>> &board, vector<int> velocity);

		// Setter
		void setQueuedVelocity(vector<int> v);

		// Getters
		vector<int> getPixelPosition();
		vector<int> getTilePosition();

		// Resize
		void resize(int w, int h, int ts);

};