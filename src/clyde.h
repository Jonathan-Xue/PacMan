#pragma once

#include "ghost.h"

class Clyde : public Ghost {

	private:
		
	public:
		// Default Constructor
		Clyde();
		
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
				@param: pacman
		*/
		void update(vector<vector<Tile>> board, Pacman pacman);

		/*
			Set The targetTile
				Within 8 Units Of Pacman: homeTilePosition
				Otherwise: Pacman's tilePosition

			@param: board
			@param: pacman
		*/
		void calculateTargetTile(vector<vector<Tile>> board, Pacman pacman);

};