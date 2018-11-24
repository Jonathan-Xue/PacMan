#pragma once

#include "ghost.h"

#include "pacman.h"

class Clyde : public Ghost {

	private:
		Pacman *pacman;
		
	public:
		// Default Constructor
		Clyde();

		// Parameterized Constructor
		Clyde(Pacman *p);
		
		// Copy Constructor
		Clyde(const Clyde& other) = default;

		// Transfer Constructor
		Clyde(Clyde&& other) = default;

		// Destructor
		~Clyde();

		// Copy Assignment Operator
		Clyde& operator=(const Clyde& other) = default;

		// Transfer Assignment Operator
		Clyde& operator=(Clyde&& other) = default;

		/*
			Update
				@param: board
		*/
		void update(vector<vector<Tile>> board);

		/*
			Set The targetTile
				Within 8 Units Of Pacman: homeTilePosition
				Otherwise: Pacman's tilePosition

			@param: board
		*/
		void calculateTargetTile(vector<vector<Tile>> board);

};