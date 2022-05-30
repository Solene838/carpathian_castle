#include "Object.h"

Object::Object(int x_px, int y_px, const std::string& label, std::uint32_t id_tile) :
	x_px(x_px),
	y_px(y_px),
	label(label),
	id_tile(id_tile)
{
}

std::uint32_t Object::getIdTile() const {
	return id_tile;
}