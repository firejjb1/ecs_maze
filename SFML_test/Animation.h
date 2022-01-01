#pragma once
#include "Common.h"

class Animation 
{
	sf::Sprite sprite;
	int frameCount;
	int currentFrame;
	int speed;
	Vec2 size;
	std::string name;
	int frameWidth;
	int frameHeight;
	bool repeat = true;
	bool flipH;
	bool flipV;

public:
	Animation() {}
	Animation(std::string name, sf::Sprite sprite, int frameCount, int speed);
	void update();
	bool hasEnded();
	std::string& getName();
	Vec2 &getSize();
	sf::Sprite& getSprite();
	void setRepeat(bool);
	void setFlipH(bool);
};