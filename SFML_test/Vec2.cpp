#include "Vec2.h"
#include <cmath>

bool Vec2::operator == (const Vec2& rhs) const
{
	return x == rhs.x && y == rhs.y;
}

bool Vec2::operator != (const Vec2& rhs) const
{
	return x != rhs.x || y != rhs.y;
}

Vec2 Vec2::operator + (const Vec2& rhs) const
{
	return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator - (const Vec2& rhs) const
{
	return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator / (const float val) const
{
	return Vec2(x / val, y / val);
}

Vec2 Vec2::operator * (const float val) const
{
	return Vec2(x * val, y * val);
}

void Vec2::operator += (const Vec2& rhs)
{
	x += rhs.x;
	y += rhs.y;
}

void Vec2::operator -= (const Vec2& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
}

void Vec2::operator *= (const float val)
{
	x *= val;
	y *= val;
}

void Vec2::operator /= (const float val)
{
	x /= val;
	y /= val;
}

float Vec2::dist(const Vec2& rhs) const
{
	return (rhs.x - x)* (rhs.x - x) + (rhs.y - y) * (rhs.y - y);
}

void Vec2::normalize()
{
	if (x == 0.0 && y == 0.0)
	{
		return;
	}
	Vec2 newVec = Vec2(x * x, y * y) / (x * x + y * y);
	x = newVec.x;
	y = newVec.y;
}


Vec2 & Vec2::operator=(const Vec2& rhs)
{
	x = rhs.x;
	y = rhs.y;
	return *this;
}
