#include "Animation.h"

Animation::Animation(std::string name, sf::Sprite sprite, int frameCount, int speed)
	:name{name}, sprite{sprite}, frameCount{frameCount}, speed{speed}
{
	size.x = sprite.getTexture()->getSize().x;
	size.y = sprite.getTexture()->getSize().y;
	frameWidth = size.x / frameCount;
	frameHeight = size.y;
}

void Animation::update()
{
	currentFrame++;
	int frame = (currentFrame / speed) % frameCount;
	sf::IntRect rect(frame * frameWidth, 0, frameWidth, getSize().y);
	sprite.setTextureRect(rect);
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