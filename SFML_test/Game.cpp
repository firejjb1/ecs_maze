#include "Game.h"

Game::Game(const std::string& config)
{
	init(config);
}

void Game::init(const std::string& path)
{
	std::ifstream fin(path);

	// TODO
	fin >> m_playerConfig.SR >> m_playerConfig.CR >> m_playerConfig.S;

	// TODO: change default
	m_window.create(sf::VideoMode(1280, 720), "Assignment 2");
	m_window.setFramerateLimit(60);

	spawnPlayer();
}

void Game::run()
{

	while (m_running)
	{
		m_entities.update();

		// all systems
		sEnemySpawner();
		sMovement();
		sCollision();
		sUserInput();
		sRender();

		// TODO: implement pause
		if(m_paused)
		{
		}

		m_currentFrame++;
	}

}

void Game::setPaused(bool paused)
{

}

void Game::spawnPlayer()
{
	auto entity = m_entities.addEntity("player");

	// TODO: spawn at middle of screen
	entity->cTransform = std::make_shared<CTransform>(Vec2(200.0f, 200.0f), Vec2(0.0f, 0.0f), 0.0f);

	entity->cShape = std::make_shared<CShape>(32.0f, 8, sf::Color(10, 10, 10), sf::Color(255, 0, 0), 4.0f);

	entity->cInput = std::make_shared<CInput>();

	m_player = entity;

}

void Game::spawnEnemy()
{
	
	auto entity = m_entities.addEntity("enemy");
	sf::Vector2u windowSize = m_window.getSize();
	Vec2 pos = Vec2((float)(rand() % windowSize.x), (float)(rand() % windowSize.y));
	Vec2 center = Vec2(windowSize.x * 0.5f, windowSize.y * 0.5f);
	Vec2 vel = (center - pos) * 0.01f;
	entity->cTransform = std::make_shared<CTransform>(pos, vel, 0.0f);

	entity->cShape = std::make_shared<CShape>(32.0f, 8, sf::Color(50, 50, 50), sf::Color(0, 255, 0), 4.0f);

}

void Game::spawnSmallEnemies(ptr<Entity> e)
{

}

void Game::spawnBullet(ptr<Entity> entity, const Vec2& mousePos)
{
	auto bulletEntity = m_entities.addEntity("bullet");
	Vec2 pos = entity->cTransform->pos;
	Vec2 dir = mousePos - pos;
	// TODO change to velocity from config
	dir.x = (dir.x >=0 ? 10 : -10) * dir.x * dir.x / (dir.x * dir.x + dir.y * dir.y);
	dir.y = (dir.y >= 0 ? 10 : -10) * dir.y * dir.y / (dir.x * dir.x + dir.y * dir.y);
	bulletEntity->cTransform = std::make_shared<CTransform>(pos, dir, 0.0f);
	bulletEntity->cShape = std::make_shared<CShape>(10.f, 8, sf::Color(0, 0, 255), sf::Color(0, 0, 255), 1.0f);
}

void Game::spawnSpecialWeapon(ptr<Entity> entity)
{
	// TODO
}

// Systems
void Game::sMovement()
{
	for (auto &entity : m_entities.getEntities())
	{
		if (entity->cInput)
		{
			entity->cTransform->velocity = { (float) (entity->cInput->right - entity->cInput->left)*10.f,
				(float) (entity->cInput->down - entity->cInput->up)*10.f };
			// normalize velocity
			entity->cTransform->velocity.normalize();
		}
		Vec2 &pos = entity->cTransform->pos;
		const Vec2 vel = entity->cTransform->velocity;
		pos += vel;
	}
}

void Game::sUserInput()
{
	// TODO
	sf::Event e;

	while (m_window.pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
			m_window.close();
		if (e.type == sf::Event::KeyPressed)
		{
			std::cout << "key pressed: " << e.key.code << "\n";
			switch (e.key.code)
			{
			case sf::Keyboard::W:
				m_player->cInput->up = true;
				break;
			case sf::Keyboard::S:
				m_player->cInput->down = true;
				break;
			case sf::Keyboard::A:
				m_player->cInput->left = true;
				break;
			case sf::Keyboard::D:
				m_player->cInput->right = true;
				break;
			default:
				break;
			}
		}
		if (e.type == sf::Event::KeyReleased)
		{
			switch (e.key.code)
			{
			case sf::Keyboard::W:
				m_player->cInput->up = false;
				break;
			case sf::Keyboard::S:
				m_player->cInput->down = false;
				break;
			case sf::Keyboard::A:
				m_player->cInput->left = false;
				break;
			case sf::Keyboard::D:
				m_player->cInput->right = false;
				break;
			default:
				break;
			}
		}
		if (e.type == sf::Event::MouseButtonPressed)
		{
			switch (e.mouseButton.button)
			{
			case (sf::Mouse::Left):
				spawnBullet(m_player, Vec2(e.mouseButton.x, e.mouseButton.y));
			}
		}

	}

}

void Game::sLifespan()
{
	// TODO
}

void Game::sRender()
{
	m_window.clear();

	// render things
	for (auto& entity : m_entities.getEntities()) {
		entity->cShape->circle.setPosition(entity->cTransform->pos.x, entity->cTransform->pos.y);

		entity->cTransform->angle += 1.0f;
		entity->cShape->circle.setRotation(entity->cTransform->angle);

		m_window.draw(entity->cShape->circle);
	}
	m_window.display();

	// TODO
	
}

void Game::sEnemySpawner()
{
	// TODO
	if (m_currentFrame == 0 || m_currentFrame - m_lastEnemySpawnTime > 200)
	{
		spawnEnemy();
		m_lastEnemySpawnTime = m_currentFrame;
	}
}

void Game::sCollision()
{
	// TODO

	// Player enemy

	// Enemy bullet

}
