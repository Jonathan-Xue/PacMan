#include "tile.h"

Tile::Tile() {}

Tile::Tile(int x, bool p, bool pp) {
	id = x;
	standardPellet = p;
	powerPellet = pp;
}

Tile::~Tile() {}

// Getters
int Tile::getID() {
	return id;
}

bool Tile::isStandardPellet() {
	return standardPellet;
}

bool Tile::isPowerPellet() {
	return powerPellet;
}

// Setters
void Tile::setStandardPellet(bool sp) {
	standardPellet = sp;
}

void Tile::setPowerPellet(bool pp) {
	powerPellet = pp;
}