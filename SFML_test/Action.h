#pragma once
#include "Common.h"

class Action
{
	const std::string name;
	const std::string type;
public:
	const std::string& getName() const;
	const std::string& getType() const;
};
