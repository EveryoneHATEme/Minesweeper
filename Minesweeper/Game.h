#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Field.h"
#include "Utils.h"
#include "Button.h"


using namespace sf;
using namespace std;


class Game {
protected:
	RenderWindow* window;
	Clock* clock;
	Event event;
	Field* field;
	Font font;
	Text cellDigits;
	Text message;
	int bombAmount;
	int fieldWidth, fieldHeight;
	int tileSize;
	Vector2i mousePos;
	Vector2i fieldPos;
	bool run;

	Texture markTexture;
	Sprite mark;

	Button* replay_button;

public:
	Game(int width, int height, const char* title, int frameLimit);
	void startGame();
	void loop();
	void update();
	void draw();
	~Game();
};