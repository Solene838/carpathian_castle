#pragma once
#include "Object.h"

class Pickable : public Object {
private:
	bool is_locked;
	int id_enigma;

public:
	Pickable(int x, int y, const std::string& label, const std::string& category, bool is_locked);
	explicit Pickable(const pugi::xml_node& node);
	bool getLock();
	void setLock(bool tmp);
};