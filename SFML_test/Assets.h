#pragma once
#include "Animation.h"

class Assets
{
	std::map<std::string, sf::Texture> textures;
	std::map<std::string, Animation> animations;
	std::map<std::string, sf::Sound> sounds;
	std::map<std::string, sf::Font> fonts;

public:
	void addTexture(std::string name, std::string path);
	void addAnimation(std::string name, Animation animation);
	void addSounds(std::string name, std::string path);
	void addFonts(std::string name, std::string path);

	sf::Texture& getTexture(std::string name);
	Animation& getAnimation(std::string name);
	sf::Sound& getSound(std::string name);
	sf::Font& getFont(std::string name);
};