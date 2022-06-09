#pragma once
#include "Object.h"

class Doors : public Object {
private:
	int room;

public:
	Doors(int x, int y, const std::string& label, const std::string& category, int room);
	explicit Doors(const pugi::xml_node& node);
};