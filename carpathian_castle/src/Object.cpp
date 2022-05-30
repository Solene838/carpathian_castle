#include "Object.h"

Object::Object(int x, int y, const std::string& label) :
	x(x),
	y(y),
	label(label)
{
}

void Object::setSprite(std::string path) {
	sf::Texture texture;
	texture.loadFromFile(path);
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
}

sf::Sprite Object::getSprite() {
	return sprite;
}