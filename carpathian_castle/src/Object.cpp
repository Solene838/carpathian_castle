#include "Object.h"

Object::Object(int x, int y, const std::string& label) :
	x(x),
	y(y),
	label(label)
{
}

void Object::setSprite(const sf::Texture& texture) {

	sprite.setTexture(texture);
	sprite.setPosition(x, y);
	boxCollider.left = x - 10;
	boxCollider.top = y;
	boxCollider.height = 500;
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