#include "Game.h"
#include <iostream>


Game::Game(int width, int heigth, const char* title, int frameLimit) {
	window = new RenderWindow(VideoMode(width, heigth), title);
	window->setFramerateLimit(frameLimit);

	fieldWidth = 10;
	fieldHeight = 10;
	bombAmount = 10;
	mousePos = Vector2i(-1, -1);
	fieldPos = Vector2i(-1, -1);

	if (!font.loadFromFile("arial.ttf")) {
		cout << "Error. Can't load font!\n";
		exit(1);
	}
	cellDigits.setFont(font);
	cellDigits.setFillColor(Color::Black);
	message.setFont(font);
	message.setFillColor(Color::Black);

	if (!markTexture.loadFromFile("mark.png")) {
		cout << "Error. Can't load image!\n";
		exit(1);
	}
	mark.setTexture(markTexture);

	replay_button = new Button(Vector2i(window->getSize().x - 50, window->getSize().y - 50),
							   Vector2i(50, 50), 
							   "replay_button.png");

	clock = new Clock();
	startGame();
}


void Game::startGame() {
	field = new Field(fieldWidth, fieldHeight, bombAmount);
	tileSize = Utils::getTileSize(Vector2i(fieldWidth, fieldHeight), window->getSize());
	run = true;
	cellDigits.setCharacterSize(tileSize);
	mark.setScale(tileSize / mark.getLocalBounds().width, tileSize / mark.getLocalBounds().height);
}


void Game::draw() {
	window->clear(Color::White);

	RectangleShape rect(Vector2f(tileSize, tileSize));
	rect.setOutlineThickness(2.f);
	rect.setOutlineColor(Color::Black);

	for (int x = 0; x < fieldWidth; x++) {
		for (int y = 0; y < fieldHeight; y++) {

			Cell* current_cell = field->getCell(x, y);
			rect.setPosition(Utils::windowCoords(Vector2i(x, y), Vector2i(fieldWidth, fieldHeight), tileSize, window->getSize()));
			bool draw_text = false;
			bool draw_mark = false;

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

			else if (field->isMarked(x, y)) {
				mark.setPosition(rect.getPosition());
				rect.setFillColor(Color::Color(Uint8(128), Uint8(128), Uint8(128), Uint8(255)));
				draw_mark = true;
			}

			else 
				rect.setFillColor(Color::Color(Uint8(128), Uint8(128), Uint8(128), Uint8(255)));

			window->draw(rect);
			if (draw_text)
				window->draw(cellDigits);
			if (draw_mark) 
				window->draw(mark);
		}
	}

	window->draw(*(replay_button->getSprite()));

	if (!run) {
		if (field->isWin())
			message.setString("You won!");
		else
			message.setString("You lose!");
		Vector2f zeroCell = Utils::windowCoords(Vector2i(0, 0), Vector2i(fieldWidth, fieldHeight), tileSize, window->getSize());
		float message_x = zeroCell.x + fieldWidth * tileSize / 2 - message.getLocalBounds().width / 2;
		float message_y = zeroCell.y - message.getLocalBounds().height * 2;
		message.setPosition(message_x, message_y);
		window->draw(message);
	}

	window->display();
}


void Game::update() {
	clock->restart();
	draw();
}


void Game::loop() {
	while (window->isOpen()) {
		while (window->pollEvent(event)) {
			switch (event.type)
			{

			case sf::Event::Closed:
				window->close();
				break;

			case Event::MouseMoved:
				replay_button->checkMouse(Vector2i(event.mouseMove.x, event.mouseMove.y));
				break;

			case sf::Event::MouseButtonPressed:
				switch (event.mouseButton.button)
				{
				case sf::Mouse::Left:
					mousePos = Vector2i(event.mouseButton.x, event.mouseButton.y);
					fieldPos = Utils::getFieldCoords(mousePos, Vector2i(fieldWidth, fieldHeight), tileSize, window->getSize());
					if (run && Utils::pointInField(fieldPos, fieldWidth, fieldHeight) && !field->isOpen(fieldPos)) {
						field->openCell(fieldPos);
						run = !field->isWin() && !(field->getCell(fieldPos)->bomb);
					}
					else {
						replay_button->checkMouse(mousePos, true);
						if (replay_button->isClicked())
							startGame();
					}
					break;

				case sf::Mouse::Right:
					mousePos = Vector2i(event.mouseButton.x, event.mouseButton.y);
					fieldPos = Utils::getFieldCoords(mousePos, Vector2i(fieldWidth, fieldHeight), tileSize, window->getSize());
					if (run && Utils::pointInField(fieldPos, fieldWidth, fieldHeight) && !field->isOpen(fieldPos)) {
						field->setMark(fieldPos);
						run = !field->isWin();
					}

				default:
					break;
				}
				break;

			default:
				break;
			}
		}
		update();
	}
}


Game::~Game() {
	delete clock;
	delete window;
}
