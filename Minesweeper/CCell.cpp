#include "CCell.h"


CCell::CCell(CellState state, bool bomb) {
	this->state = state;
	this->bomb = bomb;
	this->neighbors = 0;
}


void CCell::plantBomb() {
	this->bomb = true;
}

void CCell::addNeighbor() {
	this->neighbors++;
	if (neighbors > 8)
		printf("An error has occurred: cell neighbors count is more than 8!");
}

int CCell::getNeighborsCount() {
	return this->neighbors;
}