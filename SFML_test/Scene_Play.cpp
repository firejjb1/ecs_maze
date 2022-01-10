#include "Scene_Play.h"
#include "Game.h"
#include "Physics.h"
 
Scene_Play::Scene_Play(std::shared_ptr<Game> game, const std::string & levelPath):
	levelPath{levelPath}, Scene(game)
{
	init();
};

void Scene_Play::init()
{
	m_gridSize = { GameEngine->window().getSize().x / 10.f, GameEngine->window().getSize().y / 10.f };

	registerAction(sf::Keyboard::P, "PAUSE");
	registerAction(sf::Keyboard::Escape, "Quit");
	registerAction(sf::Keyboard::T, "TOGGLE_TEXTURE");
	registerAction(sf::Keyboard::C, "TOGGLE_COLLISION");
	registerAction(sf::Keyboard::G, "TOGGLE_GRID");
	
	m_gridText.setCharacterSize(12);
	m_gridText.setFont(GameEngine->assets().getFont("Arial"));

	loadLevel(levelPath);
}

void Scene_Play::loadLevel(const std::string & levelPath)
{
	entities = EntityManager();
	// read level file and add approriate entities
	int GX, GY;
	float CW, CH, SX, SY, SM, GV;
	std::string B;
	std::string name;
	std::ifstream levelin(levelPath);
	std::string type;

	while (levelin >> type)
	{
		if (type == "Player")
		{
			levelin >> GX >> GY >> CW >> CH >> SX >> SY >> SM >> GV >> B;
			playerConfig = { GX, GY, CW, CH, SX, SY, SM, GV, B };
			spawnPlayer();
		}

		if (type == "Enemy")
		{
			levelin >> name >> GX >> GY >> CW >> CH >> SX >> SY >> SM >> GV;
			enemyConfig.push_back({ name, GX, GY, CW, CH, SX, SY, SM, GV });
		}

		if (type == "Tile")
		{
			// Tile N GX GY
			levelin >> name >> GX >> GY;
			tileConfig.push_back({ name, GX, GY });
		}
	}

	spawnTiles();
	
}

void Scene_Play::sEnemySpawner()
{
	if (entities.getEntities("Enemy").size() == 0)
	{
		for (auto eConfig : enemyConfig)
		{
			std::shared_ptr<Entity> e = entities.addEntity("Enemy");
			Animation& anim = GameEngine->assets().getAnimation(eConfig.name + "IdleAnim");
			e->addComponent<CAnimation>(anim, true);
			e->addComponent<CTransform>(gridToMidPixel(eConfig.GX, eConfig.GY, e), Vec2(0.0, 0.0), Vec2(1.0, 1.0), 0.0);

			// e->addComponent<CBoundingBox>(Vec2(eConfig.CW, eConfig.CH));
			e->addComponent<CBoundingBox>(anim.getSize());
		}
	}
}

Vec2 Scene_Play::gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity)
{
	return Vec2(gridX * m_gridSize.x - m_gridSize.x / 2.0, gridY * m_gridSize.y - m_gridSize.y / 2.0);
}

void Scene_Play::spawnPlayer()
{
	player = entities.addEntity("Player");
	Animation &playerAnim = GameEngine->assets().getAnimation("PlayerIdleAnim");
	player->addComponent<CAnimation>(playerAnim, true);
	player->addComponent<CTransform>(gridToMidPixel(playerConfig.GX, playerConfig.GY, player), Vec2(0.0, 0.0), Vec2(2.0, 2.0), 0.0);
	player->addComponent<CBoundingBox>(Vec2(playerConfig.CW, playerConfig.CH));
	player->addComponent<CInput>(); 
	player->addComponent<CState>("Idle");
	// TODO
}

void Scene_Play::spawnTiles()
{
	for (auto config: tileConfig)
	{
		std::shared_ptr<Entity> tile = entities.addEntity("Tile");
		tile->addComponent<CAnimation>(GameEngine->assets().getAnimation(config.name), true);
		auto pos = gridToMidPixel(config.GX, config.GY, tile);
		tile->addComponent<CTransform>(pos, Vec2(0.0, 0.0), Vec2(1.0, 1.0), 0.0);
		tile->addComponent<CBoundingBox>(tile->getComponent<CAnimation>().animation.getSize());
	}
}

void Scene_Play::update()
{
	entities.update();
	sMovement();
	sLifespan();
	sCollision();
	sAnimation();
	sEnemySpawner();
	sRender();
}

void Scene_Play::doAction(const Action& action)
{
	sDoAction(action);
	std::cout << action.getName() << std::endl;

}

void Scene_Play::sDoAction(const Action &action)
{
	if (action.getType() == "Start")
	{
		if (action.getName() == "TOGGLE_TEXTURE") 
		{
			m_drawTextures = !m_drawTextures;
		}
		else if (action.getName() == "TOGGLE_COLLISION")
		{
			m_drawCollision = !m_drawCollision;
		}
		else if (action.getName() == "TOGGLE_GRID")
		{
			m_drawGrid = !m_drawGrid;
		}
		else if (action.getName() == "PAUSE")
		{
			m_paused = !m_paused;
		}
		else if (action.getName() == "PLAYER_MOVE_UP")
		{
			player->getComponent<CInput>().up = true;
		}
		else if (action.getName() == "PLAYER_MOVE_DOWN")
		{
			player->getComponent<CInput>().down = true;
		}
		else if (action.getName() == "PLAYER_MOVE_LEFT")
		{
			player->getComponent<CInput>().left = true;
			player->getComponent<CState>().facing = "Left";
		}
		else if (action.getName() == "PLAYER_MOVE_RIGHT")
		{
			player->getComponent<CInput>().right = true;
			player->getComponent<CState>().facing = "Right";
		}
		else if (action.getName() == "QUIT")
		{
			onEnd();
		}
	
	}
	else if (action.getType() == "End")
	{
		if (action.getName() == "PLAYER_MOVE_UP")
		{
			player->getComponent<CInput>().up = false;
		}
		else if (action.getName() == "PLAYER_MOVE_DOWN")
		{
			player->getComponent<CInput>().down = false;
		}
		else if (action.getName() == "PLAYER_MOVE_LEFT")
		{
			player->getComponent<CInput>().left = false;
		}
		else if (action.getName() == "PLAYER_MOVE_RIGHT")
		{
			player->getComponent<CInput>().right = false;
		}
	}
}

void Scene_Play::onEnd()
{
	GameEngine->changeScene("MENU", nullptr, true);
}

void Scene_Play::sLifespan()
{

}

void Scene_Play::sRender()
{
	if (!m_paused) { GameEngine->window().clear(sf::Color(100, 100, 255)); }
	else { GameEngine->window().clear(sf::Color(50, 50, 150)); }

	// set viewport of window to be centered on player if it's far enough right
	auto& pPos = player->getComponent<CTransform>().pos;
	float windowCenterX = std::max(GameEngine->window().getSize().x / 2.0f, pPos.x);
	sf::View view = GameEngine->window().getView();
	view.setCenter(windowCenterX, GameEngine->window().getSize().y - view.getCenter().y);
	GameEngine->window().setView(view);

	if (m_drawTextures)
	{
		for (auto e : entities.getEntities())
		{
			auto& transform = e->getComponent<CTransform>();

			if (e->hasComponent<CAnimation>())
			{
				auto& animation = e->getComponent<CAnimation>().animation;
				animation.getSprite().setRotation(transform.angle);
				animation.getSprite().setPosition(transform.pos.x, transform.pos.y);
				animation.getSprite().setScale(transform.scale.x, transform.scale.y);
				GameEngine->window().draw(animation.getSprite());
			}

		}
	}

	if (m_drawCollision)
	{
		for (auto e : entities.getEntities())
		{
			if (e->hasComponent<CBoundingBox>())
			{
				auto& box = e->getComponent<CBoundingBox>();
				auto& transform = e->getComponent<CTransform>();
				sf::RectangleShape rect;
				rect.setSize(sf::Vector2f(box.size.x - 1, box.size.y - 1));
				rect.setOrigin(sf::Vector2f(box.halfSize.x, box.halfSize.y));
				rect.setPosition(transform.pos.x, transform.pos.y);
				rect.setFillColor(sf::Color(0, 0, 0, 0));
				rect.setOutlineColor(sf::Color(255, 255, 255, 255));
				rect.setOutlineThickness(1);
				GameEngine->window().draw(rect);
			}
		}
	}

	if (m_drawGrid)
	{
		float width = GameEngine->window().getSize().x;
		float height = GameEngine->window().getSize().y;
		float leftX = GameEngine->window().getView().getCenter().x - width / 2;
		float rightX = leftX + width + m_gridSize.x;
		float nextGridX = leftX - ((int)leftX % (int)m_gridSize.x);

		for (float x = nextGridX; x < rightX; x += m_gridSize.x)
		{
			drawLine(Vec2(x, 0), Vec2(x, height));
		}

		for (float y = 0; y < height; y += m_gridSize.y)
		{
			drawLine(Vec2(leftX, height - y), Vec2(rightX, height - y));
			for (float x = nextGridX; x < rightX; x += m_gridSize.x)
			{
				std::string xCell = std::to_string((int)x / (int)m_gridSize.x);
				std::string yCell = std::to_string((int)y / (int)m_gridSize.y);
				m_gridText.setString("(" + xCell + "," + yCell + ")");
				m_gridText.setPosition(x + 3, height - y - m_gridSize.y + 2);
				GameEngine->window().draw(m_gridText);
			}
		}

	}
	GameEngine->window().display();
}


void Scene_Play::sMovement()
{
	auto& pTransform = player->getComponent<CTransform>();
	auto& pInput = player->getComponent<CInput>();
	auto& pAnimation = player->getComponent<CAnimation>().animation;
	Vec2 playerV(pInput.right - pInput.left, pInput.down - pInput.up);
	playerV *= playerConfig.SX;
	
	if (playerV.dist(Vec2(0.f, 0.f)) > 0.f)
	{
		player->getComponent<CState>().state = "Run";
	}
	else 
	{
		player->getComponent<CState>().state = "Idle";
	}

	pTransform.velocity = playerV;
	pTransform.prevPos = Vec2(pTransform.pos);
	pTransform.pos += pTransform.velocity;
	// gravity
	// maximum gravity speed in x y

	if (player->getComponent<CState>().facing == "Left")
	{
		pAnimation.setFlipH(true);
	}
	else {
		pAnimation.setFlipH(false);
	}
}

void Scene_Play::sCollision()
{
	// check if player has fallen down hole
	// don't walk off left side of the map
	for (auto e : entities.getEntities("Enemy"))
	{
		if (Physics::isCollision(player, e))
		{
			Vec2 ov = Physics::getOverlap(player, e);
			player->getComponent<CTransform>().pos = player->getComponent<CTransform>().prevPos;
		}
	}
}

void Scene_Play::sAnimation()
{
	for (auto entity : entities.getEntities())
	{
		if (entity->hasComponent<CAnimation>())
		{
			auto & anim = entity->getComponent<CAnimation>().animation;
			if (entity->hasComponent<CState>())
			{
				std::string animName = entity->tag() + entity->getComponent<CState>().state + "Anim";
				if (anim.getName() != animName)
				{
					anim = GameEngine->assets().getAnimation(animName);
				}
			}
		
			anim.update();
			if (anim.hasEnded())
			{
				entity->destroy();
			}
		}
	}
}

void Scene_Play::drawLine(const Vec2& p1, const Vec2& p2)
{
	sf::Vertex line[] = { sf::Vector2f(p1.x, p1.y), sf::Vector2f(p2.x, p2.y) };
	GameEngine->window().draw(line, 2, sf::Lines);
}
