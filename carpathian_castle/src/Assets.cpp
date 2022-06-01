#include "Assets.h"
#include <iostream>

Assets::Assets() {
	/*bookBlue.loadFromFile("resources/Sprite/bookBlue.png");
	bookGreen.loadFromFile("resources/Sprite/bookGreen.png");
	bookRed.loadFromFile("resources/Sprite/bookRed.png");
	largePosterBottom.loadFromFile("resources/Sprite/largePosterBottom.png");
	largePosterTop.loadFromFile("resources/Sprite/largePosterTop.png");
	poster.loadFromFile("resources/Sprite/poster.png");
	purse.loadFromFile("resources/Sprite/purse.png");
	skull.loadFromFile("resources/Sprite/skull.png");*/
}

const std::map<std::string, sf::Texture>& Assets::getTexturesMap() const
{
	return textures;
}

void Assets::addToMap(std::string label)
{
	sf::Texture t;
	if (std::string path = "resources/Sprite/" + label + ".png"; !t.loadFromFile(path)) std::cerr << "Didn't manage to load" << std::endl;
	textures.try_emplace(label, t);
}
