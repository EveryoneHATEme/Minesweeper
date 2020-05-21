#include "Utils.h"


Vector2f Utils::windowCoords(Vector2i field_coords, Vector2i field_size, int tile_size, Vector2u win_size) {
	int x = win_size.x / 2 - field_size.x * tile_size / 2 + tile_size * field_coords.x;
	int y = win_size.y / 2 - field_size.y * tile_size / 2 + tile_size * field_coords.y;
	return Vector2f(x, y);
}


int Utils::getTileSize(Vector2i field_size, Vector2u win_size) {
	return min(win_size.x, win_size.y - 50) / max(field_size.x, field_size.y);
}


Vector2i Utils::getFieldCoords(Vector2i mouse_position, Vector2i field_size, int tile_size, Vector2u win_size) {
	int field_x1 = win_size.x / 2 - field_size.x * tile_size / 2;
	int field_y1 = win_size.y / 2 - field_size.y * tile_size / 2;
	int field_x2 = win_size.x / 2 + field_size.x * tile_size / 2;
	int field_y2 = win_size.y / 2 + field_size.y * tile_size / 2;
	
	if (mouse_position.x < field_x1 || mouse_position.x > field_x2)
		return Vector2i(-1, 0);
	if (mouse_position.y < field_y1 || mouse_position.y > field_y2)
		return Vector2i(0, -1);

	return Vector2i((mouse_position.x - field_x1) / tile_size, (mouse_position.y - field_y1) / tile_size);
}


bool Utils::pointInField(Vector2i fieldPos, int fieldWidth, int fieldHeight) {
	return 0 <= fieldPos.x && fieldPos.x < fieldWidth && 0 <= fieldPos.y && fieldPos.y < fieldHeight;
}