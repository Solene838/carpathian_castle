#include "Enigma.h"

Enigma::Enigma(pugi::xml_node node) :
	id(node.attribute("id").as_int()),
	enigma(node.attribute("enigma").as_string()),
	answer(node.attribute("answer").as_string())
{

}