#include "CCell.h"


CCell::CCell(CellState state, BombState bomb) {
	this->state = state;
	this->bomb = bomb;
}


void CCell::plantBomb() {
	this->bomb = Planted;
}