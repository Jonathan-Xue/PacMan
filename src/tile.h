#pragma once

/*
	Tile Class
		ID:
			-1	-> Invalid Block
			0	-> Wall
			1	-> Valid Block
		Pellet:
			Type Of Pellet Within A Valid Block (None, Standard, Power)
*/
class Tile {

	private:
		int id;
		bool standardPellet;
		bool powerPellet;

	public:
		// Constructors
		Tile();
		Tile(int x, bool sp, bool pp);
		~Tile();

		// Getters
		int getID();
		bool isStandardPellet();
		bool isPowerPellet();

		// Setters
		void setStandardPellet(bool sp);
		void setPowerPellet(bool pp);

};