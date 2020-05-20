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
	if (!font.loadFromFile("arial.ttf")) {
		cout << "Error. Can't load font!";
		exit(1);
	}
	cellDigits.setFont(font);
	cellDigits.setFillColor(Color::Black);
	message.setFont(font);
	message.setFillColor(Color::Black);
	clock = new Clock();
	startGame();
}


void CGame::startGame() {
	field = new CField(fieldWidth, fieldHeight, bombAmount);
	tileSize = CUtils::getTileSize(Vector2i(fieldWidth, fieldHeight), window->getSize());
	run = true;
	cellDigits.setCharacterSize(tileSize);
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
			bool draw_text = false;

			if (field->isOpen(x, y)) {

				if (field->getCell(x, y)->bomb)
					rect.setFillColor(Color::Red);
				else {
					rect.setFillColor(Color::White);

					if (field->getNeighbors(x, y) != 0) {
						draw_text = true;
						cellDigits.setString(to_string(field->getNeighbors(x, y)));
						float digit_x = rect.getPosition().x + cellDigits.getLocalBounds().width / 2;
						float digit_y = rect.getPosition().y - cellDigits.getLocalBounds().height / 4;
						cellDigits.setPosition(digit_x, digit_y);
					}
				}
			}
			else 
				rect.setFillColor(Color::Color(Uint8(128), Uint8(128), Uint8(128), Uint8(255)));

			window->draw(rect);
			if (draw_text)
				window->draw(cellDigits);
		}
	}

	if (!run) {
		if (field->isWin())
			message.setString("You won!");
		else
			message.setString("You lose!");
		Vector2f zeroCell = CUtils::windowCoords(Vector2i(0, 0), Vector2i(fieldWidth, fieldHeight), tileSize, window->getSize());
		float message_x = zeroCell.x + fieldWidth * tileSize / 2 - message.getLocalBounds().width / 2;
		float message_y = zeroCell.y - message.getLocalBounds().height * 2;
		message.setPosition(message_x, message_y);
		window->draw(message);
	}

	window->display();
}


void CGame::update() {
	if (run) {
		if (CUtils::pointInField(fieldPos, fieldWidth, fieldHeight) && !field->isOpen(fieldPos)) {
			field->openCell(fieldPos);
			run = !field->isWin() && !(field->getCell(fieldPos)->bomb);
		}
	}
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
