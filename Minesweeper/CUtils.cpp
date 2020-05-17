#include "CUtils.h"


Vector2f CUtils::windowCoords(Vector2i field_coords, Vector2i field_size, int tile_size, Vector2u win_size) {
	int x = win_size.x / 2 - field_size.x * tile_size / 2 + tile_size * field_coords.x;
	int y = win_size.y / 2 - field_size.y * tile_size / 2 + tile_size * field_coords.y;
	return Vector2f(x, y);
}


int CUtils::getTileSize(Vector2i field_size, Vector2u win_size) {
	return min(win_size.x, win_size.y) / (max(field_size.x, field_size.y) + 2);
}


Vector2i CUtils::getFieldCoords(Vector2i mouse_position, Vector2i field_size, int tile_size, Vector2u win_size) {
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