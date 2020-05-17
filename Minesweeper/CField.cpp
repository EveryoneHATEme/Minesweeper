#include "CField.h"
#include <iostream>


CField::CField(int width, int height, int bombs_count) {
	this->_width = width;
	this->_height = height;
	this->bombs_count = bombs_count;

	field = new CCell**[height];

	for (int y = 0; y < height; y++) {
		field[y] = new CCell*[width];
		
		for (int x = 0; x < width; x++) {
			field[y][x] = new CCell(Hidden, None);
		}
	}
	this->plantBombs();
}


void CField::plantBombs() {
	srand(time(0));
	int count = this->bombs_count;

	while (count > 0) {
		int x = rand() % this->_width;
		int y = rand() % this->_height;
		if (this->field[y][x]->bomb != None)
			continue;
		this->field[y][x]->plantBomb();
		count--;
	}
}


Vector2i CField::getSize() {
	return Vector2i(_width, _height);
}


CCell* CField::getCell(int x, int y) {
	return this->field[y][x];
}
