#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


using namespace sf;
using namespace std;


class CGame {
protected:
	RenderWindow* window;
	Clock* clock;
	Event event;
public:
	CGame(int width, int height, const char* title, int frameLimit);
	void loop();
	void update();
	void draw();
	~CGame();
};