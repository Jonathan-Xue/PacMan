#pragma once

#include "ghost.h"
#include "blinky.h"

class Inky : public Ghost {

	private:
		
	public:
		// Constructors
		Inky();
		~Inky();
		
		// Methods
		void update(vector<vector<Tile>> board, Pacman pacman, Blinky blinky);
		void calculateTargetTile(Pacman pacman, Blinky blinky);
};