#include "Assets.h"
#include <iostream>

Assets::Assets() {

}

const std::map<std::string, sf::Texture>& Assets::getTexturesMap() const
{
	return textures;
}

void Assets::addToMap(std::string label, std::string category)
{
	sf::Texture t;
	if (std::string path = "resources/Sprite/" + category + ".png"; !t.loadFromFile(path)) std::cerr << "Didn't manage to load" << std::endl;
	textures.try_emplace(label, t);
}
