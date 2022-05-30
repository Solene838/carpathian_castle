#include "Object.h"

Object::Object(int x, int y, const std::string& label, std::uint32_t id_tile) :
	x(x),
	y(y),
	label(label),
	id_tile(id_tile)
{
}

std::uint32_t Object::getIdTile() {
	return id_tile;
}