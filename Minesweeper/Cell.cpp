#include "Cell.h"


Cell::Cell(CellState state, bool bomb) {
	this->state = state;
	this->bomb = bomb;
	this->neighbors = 0;
}


void Cell::plantBomb() {
	this->bomb = true;
}

void Cell::addNeighbor() {
	this->neighbors++;
	if (neighbors > 8)
		printf("An error has occurred: cell neighbors count is more than 8!");
}

int Cell::getNeighborsCount() {
	return this->neighbors;
}