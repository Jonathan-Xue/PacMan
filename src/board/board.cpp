#include "board.h"

// Public Methods
BoardGenerator::BoardGenerator() {
	parseBoardFromString(defaultBoardString, defaultNumRows, defaultNumCols);
}

BoardGenerator::BoardGenerator(string input, int r, int c) {
	parseBoardFromString(defaultBoardString, defaultNumRows, defaultNumCols);
}

BoardGenerator::~BoardGenerator() {}

void BoardGenerator::parseBoardFromString(string bo, int r, int c) {
	// Check Parameter Validity
	if (bo == "" || r * c != bo.length()) {
		boardString = defaultBoardString;
		numRows = defaultNumRows;
		numCols = defaultNumCols;
		std::cout << r << "\t" << c << "\t" << bo.length() << std::endl;
	}
	else {
		boardString = bo;
		numRows = r;
		numCols = c;
	}

	// Resize Board Vector
	board.resize(numRows);
	for (auto &it : board) {
		it.resize(numCols);
	}

	// Fill Board Vector
	int count = 0;
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			int val = boardString[count] - '0';
			if (val == 1) {
				board[i][j] = Tile(0, false, false);
			}
			else if (val == 2) {
				board[i][j] = Tile(1, false, false);
			}
			else if (val == 3) {
				board[i][j] = Tile(1, true, false);
			}
			else if (val == 4) {
				board[i][j] = Tile(1, false, true);
			}
			else {
				std::cerr << "Error. Board String Is Invalid" << std::endl;
				std::exit(1);
			}

			count++;
		}
	}
}

void BoardGenerator::generateStringFromBoard(vector<vector<Tile>> b) {
	// Parse Ignoring Buffers
	boardString = "";
	for (unsigned i = 0; i < b.size(); i++) {
		for (unsigned j = 0; j < b[0].size(); j++) {
			if (b[i][j].getID() == 0) {
				boardString.append("1");
			}
			else if (b[i][j].getID() == 1) {
				if (b[i][j].isStandardPellet()) {
					boardString.append("3");
				}
				else if (b[i][j].isPowerPellet()) {
					boardString.append("4");
				}
				else {
					boardString.append("2");
				}
			}
			else {
				std::cout << "Error. Vector Is Invalid" << "\t" << i << "\t" << j << std::endl;
			}
		}
	}

	// Set Variables
	board = b;
	boardString = boardString;
	numRows = b.size();
	numCols = b[0].size();
}

vector<vector<Tile>> BoardGenerator::resetBoard() {
	parseBoardFromString(boardString, numRows, numCols);
	return board;
}