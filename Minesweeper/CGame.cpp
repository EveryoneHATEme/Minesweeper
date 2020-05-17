#include "CGame.h"
#include <iostream>


CGame::CGame(int width, int heigth, const char* title, int frameLimit) {
	window = new RenderWindow(VideoMode(width, heigth), title);
	window->setFramerateLimit(frameLimit);

	fieldWidth = 10;
	fieldHeight = 16;
	bombAmount = 10;
	mousePos = Vector2i(0, 0);
	clock = new Clock();
	startGame();
}


void CGame::startGame() {
	field = new CField(fieldWidth, fieldHeight, bombAmount);
}


void CGame::draw() {
	window->clear(Color::White);
	int tileSize = CUtils::getTileSize(Vector2i(fieldWidth, fieldHeight), window->getSize());
	RectangleShape rect(Vector2f(tileSize, tileSize));
	rect.setOutlineThickness(2.f);
	rect.setOutlineColor(Color::Black);
	for (int x = 0; x < fieldWidth; x++) {
		for (int y = 0; y < fieldHeight; y++) {
			CCell* current_cell = field->getCell(x, y);
			rect.setPosition(CUtils::windowCoords(Vector2i(x, y), Vector2i(fieldWidth, fieldHeight), tileSize, window->getSize()));
			Vector2i field_coords = CUtils::getFieldCoords(mousePos, Vector2i(fieldWidth, fieldHeight), tileSize, window->getSize());
			printf("x: %d, y: %d\n", field_coords.x, field_coords.y);
			if (Vector2i(x, y) == field_coords)
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
			case sf::Event::MouseButtonPressed:
				switch (event.mouseButton.button)
				{
				case sf::Mouse::Left:
					mousePos = Vector2i(event.mouseButton.x, event.mouseButton.y);
					break;
				default:
					break;
				}
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
