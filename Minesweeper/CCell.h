#pragma once
#include "CellState.h"
#include <iostream>

class CCell
{
protected:
	int neighbors;

public:
	CellState state;
	bool bomb;

	CCell(CellState state, bool bomb);
	void addNeighbor();
	int getNeighborsCount();
	void plantBomb();
};

