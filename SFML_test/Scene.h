#pragma once
#include "EntityManager.h"
#include "Action.h"

class Game;

class Scene
{
protected: 
	std::shared_ptr<Game> GameEngine;
	EntityManager entities;
	int currentFrame;
	std::map<int, std::string> actionMap;
	bool paused;
	bool hasEnded;
	virtual void sDoAction(const Action& action) = 0;
	virtual void sRender() = 0;

public:
	Scene(std::shared_ptr<Game>);
	virtual void update() = 0;

	virtual void simulate(int);
	virtual void doAction(const Action&) = 0;
	virtual void registerAction(int, std::string);
};