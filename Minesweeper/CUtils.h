#pragma once
#include <SFML/Graphics.hpp>


using namespace std;
using namespace sf;


class CUtils
{
public:
	static Vector2f windowCoords(Vector2i field_coords, Vector2i field_size, int tile_size, Vector2u win_size);
	static int getTileSize(Vector2i field_size, Vector2u win_size);
	static Vector2i getFieldCoords(Vector2i mouse_position, Vector2i field_size, int tile_size, Vector2u win_size);
};	

