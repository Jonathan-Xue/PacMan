#pragma once

#include "ghost.h"

class Pinky : public Ghost {

	private:
		
	public:
		// Constructors
		Pinky();
		~Pinky();

		// Methods
		void update(vector<vector<Tile>> board, Pacman pacman);
		void calculateTargetTile(Pacman pacman);

};