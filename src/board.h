#pragma once

#include "tile.h"

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

/*
	Board Class
		Purpose:
			Generates A New Board & Returns It As A 2D Vector Of Tiles
*/
class Board {

	private:
		// Before & After Blank Tiles For Miscellaneous Display
		const int before = 3;
		const int after = 2;

		// Board Width, Height
		int numRows;
		int numCols;

		// Board Variables
		string default;
		vector<vector<Tile>> board;

	public:
		// Default Constructor
		Board();

		// Parameterized Constructor
		Board(int r, int c, string input);

		// Copy Constructor
		Board(const Board& other) = default;

		// Transfer Constructor
		Board(Board&& other) = default;

		// Destructor
		~Board();

		/*
			Fill Board Vector From Default String
				0: Invalid Block
				1: Wall
				2: No Dot
				3: Regular Dot
				4: Powerup Dot
		*/
		void parseBoard();

		// Getter
		vector<vector<Tile>> getBoard();

};