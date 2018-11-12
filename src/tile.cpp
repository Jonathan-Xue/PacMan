#include "tile.h"

Tile::Tile() {}

Tile::Tile(int x) {
	id = x;
}

Tile::~Tile() {}

void Tile::setID(int x) {
	id = x;
}

int Tile::getID() {
	return id;
}