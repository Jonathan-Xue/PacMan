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
		// Constructors
		Board();
		Board(int r, int c, string input);
		~Board();

		// Methods
		void parseBoard();

		// Getter
		vector<vector<Tile>> getBoard();

};