#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Button
{
public:
	Button(Vector2i position, Vector2i size, string filename);
	void checkMouse(Vector2i mousePos, bool click = false);
	Sprite* getSprite();
	bool isClicked();

protected:
	Vector2i _position;
	Vector2i _size;
	Texture texture;
	Sprite primarySprite;
	Sprite clickedSprite;
	Sprite focusedSprite;
	Sprite* currentSprite;
	bool is_clicked;
	bool is_focused;
};