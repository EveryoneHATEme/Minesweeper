#include "Button.h"


Button::Button(Vector2i position, Vector2i size, string filename) {
	_position = position;
	_size = size;
	texture.loadFromFile(filename);
	primarySprite.setTexture(texture);
	primarySprite.setScale(size.x / primarySprite.getLocalBounds().width, size.y / primarySprite.getLocalBounds().height);
	primarySprite.setPosition(position.x, position.y);

	clickedSprite.setTexture(texture);
	clickedSprite.setScale(Vector2f(primarySprite.getLocalBounds().width * 0.8, primarySprite.getLocalBounds().height * 0.8));
	clickedSprite.setPosition(position.x, position.y);

	focusedSprite.setTexture(texture);
	focusedSprite.setScale(Vector2f(primarySprite.getLocalBounds().width * 1.2, primarySprite.getLocalBounds().height * 1.2));
	focusedSprite.setPosition(position.x, position.y);

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
		}//else
			//currentSprite = &focusedSprite;
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