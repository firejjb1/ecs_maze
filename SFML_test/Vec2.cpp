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
	if (std::abs(x) > 0 && std::abs(y) > 0)
	{
		// 2(x^2) = vel^2 | 2^0.5 = vel/x | vel / 2^0.5 = x 
		x /= 1.41421;
		y /= 1.41421;
	}
}


Vec2 & Vec2::operator=(const Vec2& rhs)
{
	x = rhs.x;
	y = rhs.y;
	return *this;
}
