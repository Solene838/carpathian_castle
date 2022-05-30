#pragma once
#include <SFML/Graphics.hpp>

class Object {
private:
	int x;
	int y;
	std::string label;
	sf::Sprite sprite;
public:
	bool operator==(const Object&) const = default;
	Object(int x, int y, const std::string& label);
	void setSprite(std::string path);
	sf::Sprite getSprite();
};