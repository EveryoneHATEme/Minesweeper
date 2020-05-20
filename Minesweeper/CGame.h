#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "CField.h"
#include "CUtils.h"


using namespace sf;
using namespace std;


class CGame {
protected:
	RenderWindow* window;
	Clock* clock;
	Event event;
	CField* field;
	Font font;
	Text cellDigits;
	Text message;
	int bombAmount;
	int fieldWidth, fieldHeight;
	int tileSize;
	Vector2i mousePos;
	Vector2i fieldPos;
	bool run;

public:
	CGame(int width, int height, const char* title, int frameLimit);
	void startGame();
	void loop();
	void update();
	void draw();
	~CGame();
};