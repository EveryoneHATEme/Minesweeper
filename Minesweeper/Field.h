#pragma once
#include "Cell.h"
#include <SFML/Graphics.hpp>
#include <ctime>


using namespace sf;


class Field
{
protected:
	Cell*** field;
	Vector2i* bombsCoords;
	int _width;
	int _height;
	int _closedCellCount;
public:	
	Field(int width, int height, int bombs_count);
	int bombsCount;
	void plantBombs();
	int getNeighbors(int x, int y);
	Cell* getCell(int x, int y);
	Cell* getCell(Vector2i pos);
	void openCell(int x, int y);
	void openCell(Vector2i pos);
	bool isOpen(int x, int y);
	bool isOpen(Vector2i pos);
	void setMark(int x, int y);
	void setMark(Vector2i pos);
	bool isMarked(int x, int y);
	bool isMarked(Vector2i pos);
	bool isWin();
	Vector2i getSize();
};

