#pragma once

#include "ghost.h"

class Clyde : public Ghost {

	private:
		
	public:
		// Constructors
		Clyde();
		~Clyde();

		// Methods
		void update(vector<vector<Tile>> board, Pacman pacman);
		void calculateTargetTile(vector<vector<Tile>> board, Pacman pacman);

};