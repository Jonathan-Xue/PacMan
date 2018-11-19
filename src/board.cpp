#include "board.h"

Board::Board() {
	numRows = 31;
	numCols = 28;
	default = 
		"1111111111111111111111111111"
		"1333333333333113333333333331"
		"1311113111113113111113111131"
		"1411113111113113111113111141"
		"1311113111113113111113111131"
		"1333333333333333333333333331"
		"1311113113111111113113111131"
		"1311113113111111113113111131"
		"1333333113333113333113333331"
		"1111113111113113111113111111"
		"0000013111113113111113100000"
		"0000013112222222222113100000"
		"0000013112111001112113100000"
		"1111113112100000012113111111"
		"2222223222100000012223222222"
		"1111113112100000012113111111"
		"0000013112111111112113100000"
		"0000013112222222222113100000"
		"0000013112111111112113100000"
		"1111113112111111112113111111"
		"1333333333333113333333333331"
		"1311113111113113111113111131"
		"1311113111113113111113111131"
		"1433113333333223333333113341"
		"1113113113111111113113113111"
		"1113113113111111113113113111"
		"1333333113333113333113333331"
		"1311111111113113111111111131"
		"1311111111113113111111111131"
		"1333333333333333333333333331"
		"1111111111111111111111111111"
	;
	parseBoard();
}

Board::Board(int r, int c, string input) {
	numRows = r;
	numCols = c;
	default = input;

	parseBoard();
}

Board::~Board() {}

/*
	Fill Board Vector From Default String
		0	-> Invalid Block
		1	-> Wall
		2	-> No Dot
		3	-> Regular Dot
		4	-> Powerup Dot
*/
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
			int val = default[count] - '0';
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

// Getter
vector<vector<Tile>> Board::getBoard() {
	return board;
}