#pragma once
#include "Object.h"

class UIObjects : public Object {
private:
public:
	UIObjects(int x, int y, const std::string& label, const std::string& category);
	UIObjects(const pugi::xml_node& node);
};
