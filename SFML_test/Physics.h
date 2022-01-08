#pragma once
#include "Entity.h"

class Physics
{
public:
	static bool isCollision(ptr<Entity>, ptr<Entity>);
	static Vec2 getOverlap(ptr<Entity>, ptr<Entity>);
};
