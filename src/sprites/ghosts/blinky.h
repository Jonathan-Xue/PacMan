#pragma once

#include "sprites/ghost.h"

class Blinky : public Ghost {

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
		Set The targetTile
			Pacman's Current tilePosition
	*/
	void calculateTargetTile() override;

private:

};