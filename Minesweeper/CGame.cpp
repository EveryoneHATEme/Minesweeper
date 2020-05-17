#include "CGame.h"
#include <iostream>


CGame::CGame(int width, int heigth, const char* title, int frameLimit) {
	window = new RenderWindow(VideoMode(width, heigth), title);
	window->setFramerateLimit(frameLimit);

	fieldWidth = 10;
	fieldHeight = 10;
	bombAmount = 10;
	mousePos = Vector2i(-1, -1);
	fieldPos = Vector2i(-1, -1);
	clock = new Clock();
	startGame();
}


void CGame::startGame() {
	field = new CField(fieldWidth, fieldHeight, bombAmount);
	tileSize = CUtils::getTileSize(Vector2i(fieldWidth, fieldHeight), window->getSize());
}


void CGame::draw() {
	window->clear(Color::White);
	RectangleShape rect(Vector2f(tileSize, tileSize));
	rect.setOutlineThickness(2.f);
	rect.setOutlineColor(Color::Black);
	for (int x = 0; x < fieldWidth; x++) {
		for (int y = 0; y < fieldHeight; y++) {
			CCell* current_cell = field->getCell(x, y);
			rect.setPosition(CUtils::windowCoords(Vector2i(x, y), Vector2i(fieldWidth, fieldHeight), tileSize, window->getSize()));
			if (field->isOpen(x, y))
				if (field->getCell(x, y)->getNeighborsCount() == 0)
					rect.setFillColor(Color::Green);
				else
					rect.setFillColor(Color::Red);
			else
				rect.setFillColor(Color::White);
			window->draw(rect);
		}
	}
	window->display();
}


void CGame::update() {
	if ((0 <= fieldPos.x) && (fieldPos.x < fieldWidth) && (0 <= fieldPos.y) && (fieldPos.y < fieldHeight))
		if (!field->isOpen(fieldPos))
			field->openCell(fieldPos);
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
					fieldPos = CUtils::getFieldCoords(mousePos, Vector2i(fieldWidth, fieldHeight), tileSize, window->getSize());
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
