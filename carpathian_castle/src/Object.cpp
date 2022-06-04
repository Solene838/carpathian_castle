#include "Object.h"

Object::Object(int x, int y, const std::string& label, const std::string& category, bool is_locked) :
	x(x),
	y(y),
	label(label),
	category(category),
	is_locked(is_locked)
{
}

Object::Object(pugi::xml_node node) :
	x(node.attribute("x").as_int()),
	y(node.attribute("y").as_int()),
	label(node.attribute("label").as_string()),
	category(node.attribute("category").as_string()),
	is_locked(node.attribute("is_locked").as_bool())
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

std::string Object::getCategory() const {
	return category;
}

bool& Object::getLock() {
	return is_locked;
}

void Object::setLock(bool tmp) {
	is_locked = tmp;
}