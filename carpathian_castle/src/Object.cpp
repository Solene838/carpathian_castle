#include "Object.h"
#include "Object.h"
#include <iostream>

Object::Object(int x, int y, const std::string& label, const std::string& category) :
	x(x),
	y(y),
	label(label),
	category(category)
{
}

Object::Object(pugi::xml_node node) :
	x(node.attribute("x").as_int()),
	y(node.attribute("y").as_int()),
	label(node.attribute("label").as_string()),
	category(node.attribute("category").as_string())
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

void Object::setPosition(int new_x, int new_y)
{
	x = new_x;
	y = new_y;
}

std::string Object::getCategory() const {
	return category;
}

bool Object::getLock() {
	return false;
}

void Object::setLock(bool tmp) {}

int Object::getRoom() {
	return 0;
}

