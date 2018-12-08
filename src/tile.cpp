#include "tile.h"

Tile::Tile() {}

Tile::Tile(int x, bool p, bool pp) {
	id = x;
	standardPellet = p;
	powerPellet = pp;
}

Tile::~Tile() {}

int Tile::getID() {
	return id;
}

bool Tile::isStandardPellet() {
	return standardPellet;
}

bool Tile::isPowerPellet() {
	return powerPellet;
}

void Tile::setParams(int i, bool sp, bool pp) {
	id = i;
	standardPellet = sp;
	powerPellet = pp;
}

void Tile::setID(int i) {
	id = i;
}

void Tile::setStandardPellet(bool sp) {
	standardPellet = sp;
}

void Tile::setPowerPellet(bool pp) {
	powerPellet = pp;
}