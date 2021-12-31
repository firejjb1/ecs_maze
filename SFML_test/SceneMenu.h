#pragma once
#include "Scene.h"
#include "Common.h"

class Scene_Menu : public Scene
{
	std::vector<std::string> menuStrings;
	sf::Text menuText;
	std::vector<std::string> levelPaths;
	int menuIndex;
	void init();
	void sRender();
	void sDoAction();

public:
	void update();

};