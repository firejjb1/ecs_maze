#include "Animation.h"

Animation::Animation(std::string name, sf::Sprite sprite, int frameCount, int speed)
	:name{name}, sprite{sprite}, frameCount{frameCount}, speed{speed}
{
	size.x = sprite.getTexture()->getSize().x;
	size.y = sprite.getTexture()->getSize().y;
	frameWidth = size.x / frameCount;
	frameHeight = size.y;
	// this->sprite.setOrigin(frameWidth*0.5, frameHeight*0.7);
	this->sprite.setOrigin(frameWidth * 0.5, frameHeight * 0.5);
}

void Animation::update()
{
	currentFrame++;
	int frame = (currentFrame / speed) % frameCount;
	sf::IntRect rect(frame * frameWidth + (flipH ? frameWidth : 0), 0, frameWidth * (flipH ? - 1.f : 1.f), frameHeight);
	sprite.setTextureRect(rect);
}

void Animation::setFlipH(bool flip)
{
	if (flipH != flip)
	{
		currentFrame = 0;
	}
	flipH = flip;
}

bool Animation::hasEnded()
{
	return !repeat && currentFrame / speed > frameCount;
}

std::string& Animation::getName()
{
	return name;
}

Vec2& Animation::getSize()
{
	size.x = frameWidth;
	size.y = frameHeight;

	return size;
}

sf::Sprite& Animation::getSprite()
{

	return sprite;
}

void Animation::setRepeat(bool repeat)
{
	this->repeat = repeat;
}