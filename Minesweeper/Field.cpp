#include "Field.h"
#include <iostream>


Field::Field(int width, int height, int bombs_count) {
	_width = width;
	_height = height;
	_closedCellCount = _width * _height;
	bombsCount = bombs_count;

	field = new Cell**[_height];

	for (int y = 0; y < _height; y++) {
		field[y] = new Cell*[_width];
		
		for (int x = 0; x < _width; x++) {
			field[y][x] = new Cell(CellState::Hidden, false);
		}
	}
	this->plantBombs();
}


void Field::plantBombs() {
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


Vector2i Field::getSize() {
	return Vector2i(_width, _height);
}


int Field::getNeighbors(int x, int y) {
	return field[y][x]->getNeighborsCount();
}


Cell* Field::getCell(int x, int y) {
	return field[y][x];
}

Cell* Field::getCell(Vector2i pos) {
	return field[pos.y][pos.x];
}

void Field::openCell(int x, int y) {
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

void Field::openCell(Vector2i pos) {
	openCell(pos.x, pos.y);
}


bool Field::isOpen(int x, int y) {
	return field[y][x]->state == CellState::Open;
}

bool Field::isOpen(Vector2i pos) {
	return isOpen(pos.x, pos.y);
}


void Field::setMark(int x, int y) {
	if (field[y][x]->state == CellState::Hidden)
		field[y][x]->state = CellState::Marked;
	else if (field[y][x]->state == CellState::Marked)
		field[y][x]->state = CellState::Hidden;
}

void Field::setMark(Vector2i pos) {
	setMark(pos.x, pos.y);
}


bool Field::isMarked(int x, int y) {
	return field[y][x]->state == CellState::Marked;
}

bool Field::isMarked(Vector2i pos) {
	return isMarked(pos.x, pos.y);
}


bool Field::isWin() {
	bool all_marked = true;
	for (int i = 0; i < bombsCount; i++) {
		Vector2i coords = bombsCoords[i];
		if (field[coords.y][coords.x]->state != CellState::Marked) {
			all_marked = false;
			break;
		}
	}

	if (all_marked)
		return true;

	for (int i = 0; i < _height; i++)
		for (int j = 0; j < _width; j++)
			if (field[i][j]->state == CellState::Hidden && !(field[i][j]->bomb)) {
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