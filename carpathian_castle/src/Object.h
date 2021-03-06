#pragma once
#include <SFML/Graphics.hpp>
#include "Assets.h"
#include <pugixml.hpp>

class Object {
private:
	int x;
	int y;
	std::string label;
	std::string category;
	sf::IntRect boxCollider;
	sf::Sprite sprite;

public:
	Object(int x, int y, const std::string& label, const std::string& category);
	explicit Object(pugi::xml_node node);
	void setSprite(const sf::Texture& texture);
	sf::Sprite& getSprite();
	std::string getLabel() const;
	sf::IntRect getBoxCollider() const;
	int getX() const;
	int getY() const;
	void setPosition(int new_x, int new_y);
	std::string getCategory() const;
	virtual bool getLock();
	virtual void setLock(bool tmp);
	virtual int getRoom();
};