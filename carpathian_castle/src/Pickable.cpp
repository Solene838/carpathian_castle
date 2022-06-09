#include "Pickable.h"
#include <iostream>

Pickable::Pickable(int x, int y, const std::string& label, const std::string& category, bool is_locked) :
	Object(x, y, label, category),
	is_locked(is_locked)
{

}

Pickable::Pickable(const pugi::xml_node& node) :
	Object(node),
	is_locked(node.attribute("is_locked").as_bool())
{

}

bool Pickable::getLock() {
	return is_locked;
}

void Pickable::setLock(bool tmp) {
	std::cerr << "received lock value: " << tmp << std::endl;
	is_locked = tmp;
}