#pragma once
#include "BombState.h"
#include "CellState.h"

class CCell
{
public:
	CellState state;
	BombState bomb;
	CCell(CellState state, BombState bomb);
	void plantBomb();
};

