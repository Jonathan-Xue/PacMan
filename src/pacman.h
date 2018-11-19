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
		const int frameRate = 60;
		const double epsilon = 0.001;

		int screenWidth;
		int screenHeight;
		int tileSize;

		// Class Variables
		int lives = 3;

		vector<int> tilePosition = { 0, 0 };
		vector<double> pixelPosition = { 0, 0 };

		vector<int> currentVelocity = { 0, 0 };
		vector<int> queuedVelocity = { 0, 0 };
		
		// Separate Each Tile Into X Ticks
		double maxTick = 100.0;
		vector<double> currentTick = { maxTick / 2, maxTick / 2 };

		// Tiles Per Second
		int tilesPerSecond = 10;

		// Ticks Per Frame
		double speed = 0.0;

	public:
		// Constructors
		Pacman();
		~Pacman();

		// Methods
		void update(vector<vector<Tile>> &board);

		void eat(vector<vector<Tile>> &board);

		void updateVelocity(vector<vector<Tile>> board);
		bool checkValidVelocity(vector<vector<Tile>> board, vector<int> velocity);

		void move();

		void adjustBounds(vector<vector<Tile>> board);

		void calculatePixelPosition();

		// Getters
		int getLives();

		vector<double> getPixelPosition();
		vector<int> getTilePosition();
		vector<int> getCurrentVelocity();

		// Setter
		void setInitialPosition(vector<int> tp);
		void setQueuedVelocity(vector<int> v);

		// Resize
		void resize(int w, int h, int ts);

};