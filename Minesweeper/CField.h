#pragma once
#include "CCell.h"
#include <SFML/Graphics.hpp>
#include <ctime>


using namespace sf;


class CField
{
protected:
	CCell*** field;
	Vector2i* bombsCoords;
	int _width;
	int _height;
	int _closedCellCount;
public:	
	CField(int width, int height, int bombs_count);
	int bombsCount;
	void plantBombs();
	int getNeighbors(int x, int y);
	CCell* getCell(int x, int y);
	CCell* getCell(Vector2i pos);
	void openCell(int x, int y);
	void openCell(Vector2i pos);
	bool isOpen(int x, int y);
	bool isOpen(Vector2i pos);
	bool isWin();
	Vector2i getSize();
};

