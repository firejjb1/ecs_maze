#pragma once


class Vec2
{
public:
	float x = 0;
	float y = 0;

	Vec2() {};
	Vec2(float xin, float yin):
		x{ xin }, y{ yin }
	{};
	Vec2(const Vec2 &v2):
		x{v2.x}, y{v2.y}
	{};

	bool operator == (const Vec2& rhs) const;
	bool operator != (const Vec2& rhs) const;

	Vec2 operator + (const Vec2 &rhs) const;
	Vec2 operator - (const Vec2 &rhs) const;
	Vec2 operator / (const float val) const;
	Vec2 operator * (const float val) const;

	void operator += (const Vec2 &rhs);
	void operator -= (const Vec2 &rhs);
	void operator *= (const float val);
	void operator /= (const float val);

	float dist(const Vec2& rhs) const;

	void normalize();
};