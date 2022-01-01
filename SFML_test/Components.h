#pragma once

#include "Common.h"
#include "Animation.h"

class CTransform
{
public:
	Vec2 pos = { 0.0, 0.0 };
	bool has = false;
	Vec2 prevPos = { 0.0, 0.0 };
	Vec2 scale = { 1.0, 1.0 };
	Vec2 velocity = { 0.0, 0.0 };
	float angle = 0;
	CTransform() {}
	CTransform(const Vec2& p)
		:pos{ p } {}
	CTransform(const Vec2& p, const Vec2& v, const Vec2 & sc, float a)
		: pos(p), velocity(v), scale(sc), angle(a) {}
};

class CShape
{
public:
	sf::CircleShape circle;
	bool has = false;
	CShape(){}
	CShape(float radius, int points, const sf::Color& fill, const sf::Color& outline, float thickness)
		:circle(radius, points)
	{
		circle.setFillColor(fill);
		circle.setOutlineColor(outline);
		circle.setOutlineThickness(thickness);
		circle.setOrigin(radius, radius);
	}
};

class CCollision
{
public:
	float radius = 0;
	bool has = false;
	CCollision() {}
	CCollision(float r)
		:radius(r) {}
};


class CScore
{
public:
	int score = 0;
	bool has = false;
	CScore(){};
	CScore(int s)
		:score(s) {}
};

class CLifespan
{
public:
	int remaining = 0;
	bool has = false;
	int total = 0;
	CLifespan() {}
	CLifespan(int remaining, int total)
		:remaining(remaining), total(total)
	{}
};

class CInput
{
public:
	bool up = false;
	bool left = false;
	bool right = false;
	bool down = false;
	bool shoot = false;
	bool has = false;
	CInput() {}
};

class CBoundingBox
{
public:
	bool has = false;
	Vec2 size;
	Vec2 halfSize;
	CBoundingBox() {}
	CBoundingBox(const Vec2& s)
		: size(s), halfSize(s.x / 2, s.y / 2) {}

};

class CAnimation
{
public:
	bool has = false;
	Animation animation;
	bool repeat = false;
	CAnimation() {};
	CAnimation(const Animation & animation, bool r)
		:animation(animation), repeat(r) {}
};

class CGravity
{
public:
	bool has = false;
	float gravity = 0;
	CGravity() {}
	CGravity(float g): gravity(g) {}
};

class CState
{
public:
	bool has = false;
	std::string state = "jumping";
	CState() {}
	CState(const std::string & s) : state(s) {}
};
