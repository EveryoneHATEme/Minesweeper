#pragma once
#include "CCell.h"
#include <SFML/Graphics.hpp>
#include <ctime>


using namespace sf;


class CField
{
protected:
	CCell*** field;
	int _width;
	int _height;
	void plantBombs();
public:	
	CField(int width, int height, int bombs_count);
	int bombsCount;
	CCell* getCell(int x, int y);
	void openCell(int x, int y);
	void openCell(Vector2i pos);
	bool isOpen(int x, int y);
	bool isOpen(Vector2i pos);
	Vector2i getSize();
};

