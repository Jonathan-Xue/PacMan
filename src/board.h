#pragma once

#include "tile.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

class Board {

	private:
		string default = "";
		vector<vector<Tile>> board;

	public:
		// Constructors
		Board();
		Board(string input);
		~Board();

		// Getter
		vector<vector<Tile>> getBoard();

};