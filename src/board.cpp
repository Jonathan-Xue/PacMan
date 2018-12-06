#include "board.h"

// Public Methods
Board::Board() {
	boardString = defaultBoardString;
	numRows = 31;
	numCols = 28;
}

Board::Board(string input, int r, int c) {
	boardString = input;
	numRows = r;
	numCols = c;

	if (numRows * numCols != boardString.length()) {
		boardString = defaultBoardString;
	}

	parseBoard();
}

Board::~Board() {}

vector<vector<Tile>> Board::resetBoard() {
	parseBoard();
	return board;
}

vector<int> Board::getBufferBounds() {
	return vector<int>{ buffer[0], 0, numRows + buffer[0] - 1, numCols - 1};
}

// Private Methods
void Board::parseBoard() {
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
			if (val == 0) {
				board[i][j] = Tile(-1, false, false);
			}
			else if (val == 1) {
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

	// Buffer Display Tiles For Miscellaneous Display
	for (int i = 0; i < buffer[0]; i++) {
		board.insert(board.begin(), vector<Tile>(numCols, Tile(-1, false, false)));
	}
	for (int i = 0; i < buffer[2]; i++) {
		board.push_back(vector<Tile>(numCols, Tile(-1, false, false)));
	}
}