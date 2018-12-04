#pragma once

#include "ghost.h"

class Pinky : public Ghost {
		
	public:
		// Default Constructor
		Pinky();

		// Parameterized Constructor
		Pinky(vector<vector<Tile>> *b, Pacman *p);

		// Copy Constructor
		Pinky(const Pinky& other) = default;

		// Transfer Constructor
		Pinky(Pinky&& other) = default;

		// Destructor
		~Pinky();

		// Copy Assignment Operator
		Pinky& operator=(const Pinky& other) = default;

		// Transfer Assignment Operator
		Pinky& operator=(Pinky&& other) = default;

		/*
			Set The targetTile
				Pacman Moving Up: Four Tiles Up And Four Tiles Left Of Pacman's Current Position
				Pacman Moving Left Four Tiles Left Of Pacman's Current Position
				Pacman Moving Down: Four Tiles Down Of Pacman's Current Position
				Pacman Moving Right: Four Tiles Right Of Pacman's Current Position
		*/
		void calculateTargetTile() override;

	private:

};