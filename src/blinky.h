#pragma once

#include "ghost.h"

#include "pacman.h"

class Blinky : public Ghost {

	private:
		Pacman *pacman;
		
	public:
		// Default Constructor
		Blinky();

		// Parameterized Constructor
		Blinky(vector<vector<Tile>> *b, Pacman *p);

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
		*/
		void update();

		/*
			Set The targetTile
				Pacman's Current tilePosition
		*/
		void calculateTargetTile();

};