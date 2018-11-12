#pragma once

class Tile {

private:
	int id;
	bool edible;
	bool powerup;

public:
	// Constructors
	Tile();
	Tile(int x, bool e, bool p);
	~Tile();

	// Setter
	void setID(int x);

	// Getter
	int getID();

};