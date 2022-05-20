#include "Physics.h"

bool Physics::isCollision(ptr<Entity> e1, ptr<Entity> e2)
{
	Vec2 overlap = Physics::getOverlap(e1, e2);
	return overlap.x > 0.0 && overlap.y > 0.0;
}

Vec2 Physics::getOverlap(ptr<Entity> e1, ptr<Entity> e2)
{
	Vec2 e1pos = e1->getComponent<CTransform>().pos;
	Vec2 e1half = e1->getComponent<CBoundingBox>().halfSize;
	Vec2 e2pos = e2->getComponent<CTransform>().pos;
	Vec2 e2half = e2->getComponent<CBoundingBox>().halfSize;

	float dx = abs(e2pos.x - e1pos.x);
	float ox = e1half.x + e2half.x - dx;

	float dy = abs(e2pos.y - e1pos.y);
	float oy = e1half.y + e2half.y - dy;
	return Vec2(ox, oy);
}
