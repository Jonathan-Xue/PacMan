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

private:
	// Board Variables
	vector<vector<Tile>> board;
	const string defaultBoardString =
		"1111111111111111111111111111"
		"1333333333333113333333333331"
		"1311113111113113111113111131"
		"1411113111113113111113111141"
		"1311113111113113111113111131"
		"1333333333333333333333333331"
		"1311113113111111113113111131"
		"1311113113111111113113111131"
		"1333333113333113333113333331"
		"1111113111112112111113111111"
		"2222213111112112111113122222"
		"2222213112222222222113122222"
		"2222213112111111112113122222"
		"1111113112122222212113111111"
		"2222223222122222212223222222"
		"1111113112122222212113111111"
		"2222213112111111112113122222"
		"2222213112222222222113122222"
		"2222213112111111112113122222"
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
		"1111111111111111111111111111";
	string boardString;

	const int defaultNumRows = 31;
	const int defaultNumCols = 28;
	int numRows;
	int numCols;
};