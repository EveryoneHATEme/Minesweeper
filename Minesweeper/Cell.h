#pragma once
#include "CellState.h"
#include <iostream>

class Cell
{
protected:
	int neighbors;

public:
	CellState state;
	bool bomb;

	Cell(CellState state, bool bomb);
	void addNeighbor();
	int getNeighborsCount();
	void plantBomb();
};

