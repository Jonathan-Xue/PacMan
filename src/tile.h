#pragma once

class Tile {

private:
	int id;

public:
	// Constructors
	Tile();
	Tile(int x);
	~Tile();

	// Setter
	void setID(int x);

	// Getter
	int getID();

};