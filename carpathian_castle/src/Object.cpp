#include "Object.h"

Object::Object(int x, int y, const std::string& label, const std::string& type) :
	x(x),
	y(y),
	label(label),
	type(type)
{
}

Object::Object(pugi::xml_node node) :
	x(node.attribute("x").as_int()),
	y(node.attribute("y").as_int()),
	label(node.attribute("label").as_string()),
	type(node.attribute("category").as_string())
{

}

void Object::setSprite(const sf::Texture& texture) {
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
	boxCollider.left = x - 10;
	boxCollider.top = y - 10;
	boxCollider.height = 32;
	boxCollider.width = 32;

}

sf::Sprite& Object::getSprite() {
	return sprite;
}

std::string Object:: getLabel() const {
	return label;
}

sf::IntRect Object::getBoxCollider() const {
	return boxCollider;
}

int Object::getX() const {
	return x;
}

int Object::getY() const {
	return y;
}

std::string Object::getType() const {
	return type;
}