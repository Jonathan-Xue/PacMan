#pragma once

/*
	Tile Class
		ID:
			-1	-> Display/Invalid Block
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
		// Default Constructor
		Tile();

		// Parameterized Constructor
		Tile(int x, bool sp, bool pp);

		// Copy Constructor
		Tile(const Tile& other) = default;

		// Transfer Constructor
		Tile(Tile&& other) = default;

		// Destructor
		~Tile();

		// Copy Assignment Operator
		Tile& operator=(const Tile& other) = default;

		// Transfer Assignment Operator
		Tile& operator=(Tile&& other) = default;

		// Getters
		int getID();
		bool isStandardPellet();
		bool isPowerPellet();

		// Setters
		void setParams(int i, bool sp, bool pp);
		void setID(int i);
		void setStandardPellet(bool sp);
		void setPowerPellet(bool pp);

};