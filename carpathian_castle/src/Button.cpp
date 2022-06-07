#include "Button.h"

Button::Button(std::string t, sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color textColor)
{
	text.setString(t);
	text.setColor(textColor);
	text.setCharacterSize(charSize);
	button.setSize(size);
	button.setFillColor(bgColor);
}

void Button::setFont(sf::Font& font)
{
	text.setFont(font);
}

void Button::setBackColor(sf::Color color)
{
	button.setFillColor(color);
}

void Button::setTextColor(sf::Color color)
{
	text.setColor(color);
}

void Button::setPosition(sf::Vector2f pos) {
	button.setOrigin((button.getSize().x) / 2, (button.getSize().y) / 2);
	button.setPosition(pos);
	float xPos = (pos.x - button.getLocalBounds().width / 6) - (text.getLocalBounds().width / 6);
	float yPos = (pos.y - button.getLocalBounds().height / 3) + (text.getLocalBounds().height / 3);
	text.setPosition({xPos, yPos});
}

void Button::drawTo(sf::RenderWindow& window)
{
	window.draw(button);
	window.draw(text);
}

bool Button::isMouseOver(sf::RenderWindow& window)
{
	float mouseX = sf::Mouse::getPosition(window).x;
	float mouseY = sf::Mouse::getPosition(window).y;

	float btnPosX = button.getPosition().x;
	float btnPosY = button.getPosition().y;

	float btnxPosWidth = button.getPosition().x + button.getLocalBounds().width;
	float btnyPosHeight = button.getPosition().y + button.getLocalBounds().height;
	
	if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY) {
		return true;
	}
	return false;
}
