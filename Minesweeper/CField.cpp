#include "CField.h"
#include <iostream>


CField::CField(int width, int height, int bombs_count) {
	_width = width;
	_height = height;
	bombsCount = bombs_count;

	field = new CCell**[_height];

	for (int y = 0; y < _height; y++) {
		field[y] = new CCell*[_width];
		
		for (int x = 0; x < _width; x++) {
			field[y][x] = new CCell(Hidden, None);
		}
	}
	this->plantBombs();
}


void CField::plantBombs() {
	srand(time(0));
	int count = bombsCount;

	while (count > 0) {
		std::cout << 2 << '\n';
		int x = rand() % _width;
		int y = rand() % _height;
		if (field[y][x]->bomb != None)
			continue;
		field[y][x]->plantBomb();
		for (int i = y - 1; i <= y + 1; i++)
			for (int j = x - 1; j <= x + 1; j++) {
				if (i == y && j == x)
					continue;
				if (i < 0 || i >= _height)
					continue;
				if (j < 0 || j >= _width)
					continue;
				field[i][j]->addNeighbor();
			}
		count--;
	}
}


Vector2i CField::getSize() {
	return Vector2i(_width, _height);
}


CCell* CField::getCell(int x, int y) {
	return field[y][x];
}


void CField::openCell(int x, int y) {
	field[y][x]->state = Open;
	if (field[y][x]->getNeighborsCount() == 0)
		for (int i = y - 1; i <= y + 1; i++)
			for (int j = x - 1; j <= x + 1; j++) {
				if (i == y && j == x)
					continue;
				if (i < 0 || i >= _height)
					continue;
				if (j < 0 || j >= _width)
					continue;
				if (field[i][j]->bomb != Planted && field[i][j]->state != Open) {
					openCell(j, i);
				}
			}
}

void CField::openCell(Vector2i pos) {
	openCell(pos.x, pos.y);
}


bool CField::isOpen(int x, int y) {
	return field[y][x]->state == Open;
}

bool CField::isOpen(Vector2i pos) {
	return isOpen(pos.x, pos.y);
}