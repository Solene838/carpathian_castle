#include "UIObjects.h"

UIObjects::UIObjects(int x, int y, const std::string& label, const std::string& category) :
	Object(x, y, label, category)
{
}

UIObjects::UIObjects(const pugi::xml_node& node) :
	Object(node)
{
}
