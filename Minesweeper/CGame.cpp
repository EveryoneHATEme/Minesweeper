#include "CGame.h"


CGame::CGame(int width, int heigth, const char* title, int frameLimit) {
	window = new RenderWindow(VideoMode(width, heigth), title);
	window->setFramerateLimit(frameLimit);

	clock = new Clock();
}


void CGame::draw() {
	window->clear(Color::White);
	int tileSize = 20;
	RectangleShape rect(Vector2f(tileSize, tileSize));
	rect.setOutlineThickness(2.f);
	rect.setOutlineColor(Color::Black);

	for (int x = 0; x < 5; x++) {
		for (int y = 0; y < 5; y++) {
			rect.setPosition(Vector2f(tileSize * (x + 1), tileSize * (y + 1)));
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
		while (window->pollEvent(this->event)) {
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				window->close();
			update();
		}
	}
}


CGame::~CGame() {
	delete clock;
	delete window;
}
