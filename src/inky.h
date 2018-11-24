#pragma once

#include "ghost.h"
#include "blinky.h"

class Inky : public Ghost {

	private:
		
	public:
		// Default Constructor
		Inky();
		
		// Copy Constructor
		Inky(const Inky& other) = default;

		// Transfer Constructor
		Inky(Inky&& other) = default;

		// Destructor
		~Inky();

		// Copy Assignment Operator
		Inky& operator=(const Inky& other) = default;

		// Transfer Assignment Operator
		Inky& operator=(Inky&& other) = default;

		/*
			Update
				@param: board
				@param: pacman
				@param: blinky
		*/
		void update(vector<vector<Tile>> board, Pacman pacman, Blinky blinky);

		/*
			Set The targetTile
				Pacman Moving Up: Two Tiles Up And Two Tiles Left Of Pacman's Current Position
				Pacman Moving Left: Two Tiles Left Of Pacman's Current Position
				Pacman Moving Down:	Two Tiles Down Of Pacman's Current Position
				Pacman Moving Right:Two Tiles Right Of Pacman's Current Position
			
				Double the Corresponding Vector From Blinky To ^^^

			@param: pacman
			@param: blinky
		*/
		void calculateTargetTile(Pacman pacman, Blinky blinky);
};