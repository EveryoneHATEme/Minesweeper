#include "Button.h"
#include <iostream>


Button::Button(Vector2i position, Vector2i size, string filename) {
	_position = position;
	_size = size;
	texture.loadFromFile(filename);
	primarySprite.setTexture(texture);
	primarySprite.setScale(size.x / primarySprite.getLocalBounds().width, size.y / primarySprite.getLocalBounds().height);
	primarySprite.setPosition(position.x, position.y);

	std::cout << primarySprite.getGlobalBounds().left << ' ' << primarySprite.getGlobalBounds().top << ' ' << primarySprite.getGlobalBounds().width << ' ' << primarySprite.getGlobalBounds().height << '\n';

	clickedSprite.setTexture(texture);
	clickedSprite.setScale(Vector2f(0.8, 0.8));
	clickedSprite.setPosition(position.x, position.y);

	std::cout << clickedSprite.getGlobalBounds().left << ' ' << clickedSprite.getGlobalBounds().top << ' ' << clickedSprite.getGlobalBounds().width << ' ' << clickedSprite.getGlobalBounds().height << '\n';

	focusedSprite.setTexture(texture);
	focusedSprite.setScale(Vector2f(1.1, 1.1));
	focusedSprite.setPosition(position.x, position.y);

	std::cout << primarySprite.getPosition().x << ' ' << primarySprite.getPosition().y << '\n';
	std::cout << clickedSprite.getPosition().x << ' ' << clickedSprite.getPosition().y << '\n';
	std::cout << focusedSprite.getPosition().x << ' ' << focusedSprite.getPosition().y << '\n';

	currentSprite = &primarySprite;

	is_clicked = false;
	is_focused = false;
}


void Button::checkMouse(Vector2i mousePos, bool click) {
	FloatRect bounds = currentSprite->getGlobalBounds();

	if (bounds.contains(mousePos.x, mousePos.y)) {
		if (click) {
			currentSprite = &clickedSprite;
			is_clicked = true;
		}
		else
			currentSprite = &focusedSprite;
	}
	else {
		currentSprite = &primarySprite;
		is_clicked = false;
	}
}

Sprite* Button::getSprite() {
	return currentSprite;
}


bool Button::isClicked() {
	return is_clicked;
}