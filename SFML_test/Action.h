#pragma once
#include "Common.h"

class Action
{
	const std::string name;
	const std::string type;
public:
	Action(std::string name, std::string type) :
		name{ name }, type{ type }{};
	const std::string& getName() const;
	const std::string& getType() const;
};
