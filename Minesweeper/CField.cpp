#include "CField.h"
#include <iostream>


CField::CField(int width, int height, int bombs_count) {
	_width = width;
	_height = height;
	_closedCellCount = _width * _height;
	bombsCount = bombs_count;

	field = new CCell**[_height];

	for (int y = 0; y < _height; y++) {
		field[y] = new CCell*[_width];
		
		for (int x = 0; x < _width; x++) {
			field[y][x] = new CCell(CellState::Hidden, false);
		}
	}
	this->plantBombs();
}


void CField::plantBombs() {
	srand(time(0));
	int count = bombsCount;
	bombsCoords = new Vector2i[bombsCount];
	int index = 0;

	while (count > 0) {
		int x = rand() % _width;
		int y = rand() % _height;
		if (field[y][x]->bomb)
			continue;
		field[y][x]->plantBomb();
		bombsCoords[index] = Vector2i(x, y);
		index++;
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


int CField::getNeighbors(int x, int y) {
	return field[y][x]->getNeighborsCount();
}


CCell* CField::getCell(int x, int y) {
	return field[y][x];
}

CCell* CField::getCell(Vector2i pos) {
	return field[pos.y][pos.x];
}

void CField::openCell(int x, int y) {
	field[y][x]->state = CellState::Open;
	if (field[y][x]->getNeighborsCount() == 0)
		for (int i = y - 1; i <= y + 1; i++)
			for (int j = x - 1; j <= x + 1; j++) {
				if (i == y && j == x)
					continue;
				if (i < 0 || i >= _height)
					continue;
				if (j < 0 || j >= _width)
					continue;
				if (!(field[i][j]->bomb) && field[i][j]->state != CellState::Open) {
					openCell(j, i);
				}
			}
	_closedCellCount--;
}

void CField::openCell(Vector2i pos) {
	openCell(pos.x, pos.y);
}


bool CField::isOpen(int x, int y) {
	return field[y][x]->state == CellState::Open;
}

bool CField::isOpen(Vector2i pos) {
	return isOpen(pos.x, pos.y);
}


bool CField::isWin() {
	for (int i = 0; i < _height; i++)
		for (int j = 0; j < _width; j++)
			if (field[i][j]->state == CellState::Hidden && !(field[i][j]->bomb)) {
				printf("Closed at %d %d\n", j, i);
				return false;
			}

	for (int i = 0; i < bombsCount; i++) {
		Vector2i coords = bombsCoords[i];
		if (field[coords.y][coords.x]->state != CellState::Hidden) {
			return false;
		}
	}

	return true;
}