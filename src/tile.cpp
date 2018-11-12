#include "tile.h"

Tile::Tile() {}

Tile::Tile(int x, bool e, bool p) {
	id = x;
	edible = e;
	powerup = p;
}

Tile::~Tile() {}

void Tile::setID(int x) {
	id = x;
}

int Tile::getID() {
	return id;
}