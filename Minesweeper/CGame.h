#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "CField.h"


using namespace sf;
using namespace std;


class CGame {
protected:
	RenderWindow* window;
	Clock* clock;
	Event event;
	CField* field;
	int bombAmount;
	int fieldWidth, fieldHeight;
public:
	CGame(int width, int height, const char* title, int frameLimit);
	void startGame();
	void loop();
	void update();
	void draw();
	~CGame();
};