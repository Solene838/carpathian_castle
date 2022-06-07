#include "Text.h"

Text::Text(std::string label) :
	label(label)
{
}

void Text::setParameters(std::string display, sf::Font font, int characterSize, sf::Text::Style style, sf::Color color) {
	text.setString(display);
	text.setFont(font);
	text.setCharacterSize(characterSize);
	text.setStyle(style);
	text.setFillColor(color);
}

std::string& Text::getLabel() {
	return label;
}

sf::Text& Text::getText() {
	return text;
}