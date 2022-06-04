#include "Text.h"

Text::Text(std::string label) :
	label(label)
{
}

void Text::setText(std::string display, sf::Font font, int characterSize, sf::Text::Style style, sf::Color color, int pos_x, int pos_y) {
	text.setString(display);
	text.setFont(font);
	text.setCharacterSize(characterSize);
	text.setStyle(style);
	text.setFillColor(color);
	text.setPosition(pos_x, pos_y);
}

std::string& Text::getLabel() {
	return label;
}

sf::Text& Text::getText() {
	return text;
}