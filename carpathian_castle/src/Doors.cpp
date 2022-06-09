#include "Doors.h"
#include <iostream>

Doors::Doors(int x, int y, const std::string& label, const std::string& category, int room) :
	Object(x, y, label, category),
	room(room)
{

}

Doors::Doors(const pugi::xml_node& node) :
	Object(node),
	room(node.attribute("room").as_int())
{

}