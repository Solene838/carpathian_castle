#include "Door.h"
#include <iostream>

Door::Door(int x, int y, const std::string& label, const std::string& category, int room) :
	Object(x, y, label, category),
	room(room)
{

}

Door::Door(const pugi::xml_node& node) :
	Object(node),
	room(node.attribute("room").as_int())
{

}

int Door::getRoom() {
	return room;
}