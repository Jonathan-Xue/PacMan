#pragma once

#include "ghost.h"

#include "blinky.h"

class Inky : public Ghost {
		
	public:
		// Default Constructor
		Inky();

		// Parameterized Constructor
		Inky(vector<vector<Tile>> *bo, Pacman *p, Ghost *bl);
		
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
			Set The targetTile
				Pacman Moving Up: Two Tiles Up Of Pacman's Current Position
				Pacman Moving Left: Two Tiles Left Of Pacman's Current Position
				Pacman Moving Down:	Two Tiles Down Of Pacman's Current Position
				Pacman Moving Right:Two Tiles Right Of Pacman's Current Position
			
				Double the Corresponding Vector From Blinky To ^^^
		*/
		void calculateTargetTile() override;

	private:
		Ghost *blinky;

};