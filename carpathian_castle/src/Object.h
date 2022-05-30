#pragma once
#include <SFML/Graphics.hpp>

class Object {
private:
	int x_px;
	int y_px;
	std::string label;
	std::uint32_t id_tile;
public:
	bool operator==(const Object&) const = default;
	Object(int x_px, int y_px, const std::string& label, std::uint32_t id_tile);
	std::uint32_t getIdTile() const;
};