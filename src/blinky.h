#pragma once

#include "ghost.h"

class Blinky : public Ghost {

	private:
		
	public:
		// Constructors
		Blinky();
		~Blinky();

		// Methods
		void update(vector<vector<Tile>> board, Pacman pacman);
		void calculateTargetTile(Pacman pacman);

};