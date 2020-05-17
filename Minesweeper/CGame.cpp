#include "CGame.h"
#include <iostream>


CGame::CGame(int width, int heigth, const char* title, int frameLimit) {
	window = new RenderWindow(VideoMode(width, heigth), title);
	window->setFramerateLimit(frameLimit);

	fieldWidth = 10;
	fieldHeight = 16;
	bombAmount = 10;
	clock = new Clock();
	startGame();
}


void CGame::startGame() {
	field = new CField(fieldWidth, fieldHeight, bombAmount);
}


void CGame::draw() {
	window->clear(Color::White);
	int tileSize = min(window->getSize().x, window->getSize().y) / (max(fieldWidth, fieldHeight) + 2);
	RectangleShape rect(Vector2f(tileSize, tileSize));
	rect.setOutlineThickness(2.f);
	rect.setOutlineColor(Color::Black);
	for (int x = 0; x < fieldWidth; x++) {
		for (int y = 0; y < fieldHeight; y++) {
			CCell* current_cell = field->getCell(x, y);
			rect.setPosition(Vector2f(window->getSize().x / 2 - fieldWidth * tileSize / 2 + tileSize * x,
									  window->getSize().y / 2 - fieldHeight * tileSize / 2 + tileSize * y));
			if (current_cell->bomb == Planted)
				rect.setFillColor(Color::Red);
			else
				rect.setFillColor(Color::White);
			window->draw(rect);
		}
	}
	window->display();
}


void CGame::update() {
	clock->restart();
	draw();
}


void CGame::loop() {
	while (window->isOpen()) {
		while (window->pollEvent(event)) {
			switch (event.type)
			{
			case sf::Event::Closed:
				window->close();
				break;
			default:
				break;
			}
		}
		update();
	}
}


CGame::~CGame() {
	delete clock;
	delete window;
}
