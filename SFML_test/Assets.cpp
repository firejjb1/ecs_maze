#include "Assets.h"


void Assets::addTexture(std::string name, std::string path)
{
	sf::Texture tex;
	tex.loadFromFile(path);
	textures[name] = tex;
}

void Assets::addAnimation(std::string name, Animation animation)
{
	animations[name] = animation;
}

void Assets::addSounds(std::string name, std::string path)
{
	sf::SoundBuffer buffer;
	buffer.loadFromFile(path);
	sf::Sound sd;
	sd.setBuffer(buffer);
	sounds[name] = sd;
}

void Assets::addFonts(std::string name, std::string path)
{
	sf::Font ft;
	ft.loadFromFile(path);
	fonts[name] = ft;
}

sf::Texture& Assets::getTexture(std::string name)
{
	return textures[name];
}

Animation& Assets::getAnimation(std::string name)
{
	return animations[name];
}

sf::Sound& Assets::getSound(std::string name)
{
	return sounds[name];
}

sf::Font& Assets::getFont(std::string name)
{
	return fonts[name];
}
