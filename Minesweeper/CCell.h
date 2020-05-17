#pragma once
#include "BombState.h"
#include "CellState.h"
#include <iostream>

class CCell
{
protected:
	int neighbors;

public:
	CellState state;
	BombState bomb;

	CCell(CellState state, BombState bomb);
	void addNeighbor();
	int getNeighborsCount();
	void plantBomb();
};

