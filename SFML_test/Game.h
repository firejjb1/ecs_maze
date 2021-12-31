#pragma once

#include "Common.h"
#include "Scene.h"
#include "Assets.h"

#include <memory>

typedef std::map<std::string, std::shared_ptr<Scene>> SceneMap;

class Game
{
	sf::RenderWindow m_window;
	Assets m_assets;
	std::string m_currentScene;
	SceneMap m_sceneMap;
	size_t m_simulationSpeed = 1;
	bool m_running = true;
	void init(const std::string& config);
	void update();
	void sUserInput();
	std::shared_ptr<Scene> currentScene();


public:

	Game(const std::string& config);
	void changeScene(const std::string& sceneName, std::shared_ptr<Scene> scene, bool endCurrentScene = false);

	void quit();
	void run();

	sf::RenderWindow& window();
	Assets& assets();
	bool isRunning();
};
