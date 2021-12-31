#include "Scene_Play.h"
#include "Game.h"
 
Scene_Play::Scene_Play(std::shared_ptr<Game> game, const std::string & levelPath):
	levelPath{levelPath}, Scene(game)
{
	init();
};

void Scene_Play::init()
{
	registerAction(sf::Keyboard::P, "PAUSE");
	registerAction(sf::Keyboard::Escape, "Quit");
	registerAction(sf::Keyboard::T, "TOGGLE_TEXTURE");
	registerAction(sf::Keyboard::C, "TOGGLE_COLLISION");
	registerAction(sf::Keyboard::G, "TOGGLE_GRID");
	// add controls
	m_gridText.setCharacterSize(12);
	m_gridText.setFont(GameEngine->assets().getFont("Arial"));

	loadLevel(levelPath);
}

void Scene_Play::loadLevel(const std::string & levelPath)
{
	entities = EntityManager();
	// read level file and add approriate entities
	// use PlayerConfig
	spawnPlayer();
	// sample
	/**
	
	auto brick = entities.addEntity("tile");
	brick->addComponent<CAnimation>(GameEngine->assets().getAnimation("Brick"), true);
	brick->addComponent<CTransform>(Vec2(96, 480));
	if (brick->getComponent<CAnimation>().animation.getName() == "Brick")
	{
		// tile is a brick
	}

	auto block = entities.addEntity("tile");
	block->addComponent<CAnimation>(GameEngine->assets().getAnimation("Block"), true);
	block->addComponent<CTransform>(Vec2(224, 480));
	block->addComponent<CBoundingBox>(GameEngine->assets().getAnimation("Block").getSize());
	*/
	// make sure use reference for components
}

Vec2 Scene_Play::gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity)
{
	return Vec2(gridX * m_gridSize.x, gridY * m_gridSize.y);
}

void Scene_Play::spawnPlayer()
{
	player = entities.addEntity("player");
	player->addComponent<CAnimation>(GameEngine->assets().getAnimation("PlayerIdleAnim"), true);
	player->addComponent<CTransform>(Vec2(0, 0));
	player->addComponent<CBoundingBox>(Vec2(120, 80));
	// TODO
}

void Scene_Play::update()
{
	entities.update();
	// TODO pause
	sMovement();
	sLifespan();
	sCollision();
	sAnimation();
	sRender();
	
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
		else if (action.getName() == "QUIT")
		{
			onEnd();
		}
	
	}
	else if (action.getType() == "END")
	{

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
	if (!m_paused) { GameEngine->window().clear(sf::Color(100, 100, 255));}
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
	
	Vec2 playerV(0, 0);



	pTransform.velocity = playerV;
	pTransform.pos += pTransform.velocity;
	// player movement based on cInput
	// gravity
	// maximum gravity speed in x y
	// note, set entity's scale.x to -1 to face left
}

void Scene_Play::sCollision()
{
	// implement Physics::GetOverlap
	// check if player has fallen down hole
	// don't walk off left side of the map
}

void Scene_Play::sAnimation()
{
	// complete Animation class
	// set animation based on CState
	// for each entity with animation, call entity->getComponent<CAnimation>().animation.update()
	// if not repeat animation and has ended, destroy entity
	for (auto entity : entities.getEntities())
	{
		if (entity->hasComponent<CAnimation>())
		{
			auto & anim = entity->getComponent<CAnimation>().animation;
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
