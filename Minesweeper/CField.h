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
	int bombs_count;
	CCell* getCell(int x, int y);
	Vector2i getSize();
};

