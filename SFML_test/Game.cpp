#include "Game.h"
#include "Scene_Play.h"

Game::Game(const std::string& config)
{
	init(config);
}

void Game::init(const std::string& path)
{
	std::ifstream assetIn(path + "/Asset.txt"); 
	std::ifstream levelIn(path + "/Level.txt");

	std::string input;
	
	// render window
	m_window.create(sf::VideoMode(1600, 900), "Survive Ina'Nis");
	m_window.setFramerateLimit(60);
	
	while (assetIn >> input)
	{
		std::string name;
		
		if (input == "Texture")
		{
			std::string texPath;
			assetIn >> name >> texPath;
			m_assets.addTexture(name, path + "/" + texPath);
		}
		else if (input == "Animation")
		{
			std::string texName;
			int frameCount;
			float animSpeed;
			assetIn >> name >> texName >> frameCount >> animSpeed;
			std::cout << "Animation " << name << " texture " << texName << " frame count " << frameCount << " animation speed " << animSpeed << "\n";
			m_assets.addAnimation(name, Animation(name, sf::Sprite(m_assets.getTexture(texName)), frameCount, animSpeed));
		}

		else if (input == "Font")
		{
			std::string fontPath;
			assetIn >> name >> fontPath;
			m_assets.addFonts(name, path + "/" + fontPath);
		}
	}

	// init scenes
	Scene_Play sceneLevel1(std::shared_ptr<Game>(this), std::string(path+"/Level.txt"));
	m_sceneMap["level1"] = std::make_shared<Scene_Play>(sceneLevel1);
	m_currentScene = "level1"; 
}

void Game::run()
{
	while (m_running)
	{
		sUserInput();
		currentScene()->update();
	}

}



void Game::sUserInput()
{
	sf::Event e;

	while (m_window.pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
			m_window.close();
		if (e.type == sf::Event::KeyPressed)
		{
			std::cout << "key pressed: " << e.key.code << "\n";
			if (e.key.code == sf::Keyboard::G)
			{
				Action newAction("TOGGLE_GRID", "Start");
				currentScene()->doAction(newAction);
			}
			else if (e.key.code == sf::Keyboard::T)
			{
				Action newAction("TOGGLE_TEXTURE", "Start");
				currentScene()->doAction(newAction);
			}
			else if (e.key.code == sf::Keyboard::C)
			{
				Action newAction("TOGGLE_COLLISION", "Start");
				currentScene()->doAction(newAction);
			}
			else if (e.key.code == sf::Keyboard::W)
			{
				Action newAction("PLAYER_MOVE_UP", "Start");
				currentScene()->doAction(newAction);
			}
			else if (e.key.code == sf::Keyboard::S)
			{
				Action newAction("PLAYER_MOVE_DOWN", "Start");
				currentScene()->doAction(newAction);
			}
			else if (e.key.code == sf::Keyboard::A)
			{
				Action newAction("PLAYER_MOVE_LEFT", "Start");
				currentScene()->doAction(newAction);
			}
			else if (e.key.code == sf::Keyboard::D)
			{
				Action newAction("PLAYER_MOVE_RIGHT", "Start");
				currentScene()->doAction(newAction);
			}
		
		}
		if (e.type == sf::Event::KeyReleased)
		{
			if (e.key.code == sf::Keyboard::W)
			{
				Action newAction("PLAYER_MOVE_UP", "End");
				currentScene()->doAction(newAction);
			}
			else if (e.key.code == sf::Keyboard::S)
			{
				Action newAction("PLAYER_MOVE_DOWN", "End");
				currentScene()->doAction(newAction);
			}
			else if (e.key.code == sf::Keyboard::A)
			{
				Action newAction("PLAYER_MOVE_LEFT", "End");
				currentScene()->doAction(newAction);
			}
			else if (e.key.code == sf::Keyboard::D)
			{
				Action newAction("PLAYER_MOVE_RIGHT", "End");
				currentScene()->doAction(newAction);
			}
		}
		if (e.type == sf::Event::MouseButtonPressed)
		{
			
		}

	}

}

Assets& Game::assets()
{
	return m_assets;
}

void Game::changeScene(const std::string& sceneName, std::shared_ptr<Scene> scene, bool endCurrentScene)
{
	m_currentScene = sceneName;
	if (scene)
		m_sceneMap[sceneName] = scene;
}

sf::RenderWindow& Game::window()
{
	return m_window;
}

std::shared_ptr<Scene> Game::currentScene()
{
	return m_sceneMap[m_currentScene];
}
