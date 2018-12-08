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
class BoardGenerator {

	public:
		// Default Constructor
		BoardGenerator();

		// Parameterized Constructor
		BoardGenerator(string input, int r, int c);

		// Copy Constructor
		BoardGenerator(const BoardGenerator& other) = default;

		// Transfer Constructor
		BoardGenerator(BoardGenerator&& other) = default;

		// Destructor
		~BoardGenerator();

		/*
			Fill Board Vector From Default String
				0: Display/Invalid Block
				1: Wall
				2: No Dot
				3: Regular Dot
				4: Powerup Dot
		*/
		void parseBoardFromString(string bo, int r, int c);

		/*
			Generates A Board String
				@param: vector<vector<int>> board
				@return: string
		*/
		void generateStringFromBoard(vector<vector<Tile>> b);

		// Reset Function
		vector<vector<Tile>> resetBoard();

		// Getters
		vector<int> getBufferBounds();

	private:
		// Before & After Blank Tiles For Miscellaneous Display
		const vector<int> buffer = vector<int>{ 3, 0, 2, 0 };

		// Board Variables
		vector<vector<Tile>> board;
		const string defaultBoardString =
			"1111111111111111311111111111"
			"1333333333333113333333333331"
			"1311113111113113111113111131"
			"1411113111113113111113111141"
			"1311113111113113111113111131"
			"1333333333333333333333333331"
			"1311113113111111113113111131"
			"1311113113111111113113111131"
			"1333333113333113333113333331"
			"1111113111112112111113111111"
			"0000013111112112111113100000"
			"0000013112222222222113100000"
			"0000013112111111112113100000"
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
			"1111111111111111311111111111";
		string boardString;

		const int defaultNumRows = 31;
		const int defaultNumCols = 28;
		int numRows;
		int numCols;
};