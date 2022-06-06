#pragma once
#include <pugixml.hpp>

class Enigma {
private:
	int id;
	std::string enigma;
	std::string answer;

public:
	explicit Enigma(pugi::xml_node node);
};