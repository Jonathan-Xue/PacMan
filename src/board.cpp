#include "board.h"

Board::Board() {
	numRows = 31;
	numCols = 28;
	boardString = defaultBoardString;
	parseBoard();
}

Board::Board(int r, int c, string input) {
	numRows = r;
	numCols = c;
	boardString = input;

	if (numRows * numCols != boardString.length()) {
		boardString = defaultBoardString;
	}

	parseBoard();
}

Board::~Board() {}

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
				std::cerr << "Error. GameState Is Invalid" << std::endl;
				std::exit(1);
			}

			count++;
		}
	}

	// Before & After Blank Tiles For Miscellaneous Display
	for (int i = 0; i < before; i++) {
		board.insert(board.begin(), vector<Tile>(numCols, Tile(-1, false, false)));
	}
	for (int i = 0; i < after; i++) {
		board.push_back(vector<Tile>(numCols, Tile(-1, false, false)));
	}
}

vector<vector<Tile>> Board::getBoard() {
	return board;
}