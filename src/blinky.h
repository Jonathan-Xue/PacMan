#pragma once

#include "ghost.h"

class Blinky : public Ghost {

	private:
		
	public:
		// Default Constructor
		Blinky();

		// Copy Constructor
		Blinky(const Blinky& other) = default;

		// Transfer Constructor
		Blinky(Blinky&& other) = default;

		// Destructor
		~Blinky();

		// Copy Assignment Operator
		Blinky& operator=(const Blinky& other) = default;

		// Transfer Assignment Operator
		Blinky& operator=(Blinky&& other) = default;

		/*
			Update
				@param: board
				@param: pacman
		*/
		void update(vector<vector<Tile>> board, Pacman pacman);

		/*
			Set The targetTile
				Pacman's Current tilePosition

			@param: pacman
		*/
		void calculateTargetTile(Pacman pacman);

};