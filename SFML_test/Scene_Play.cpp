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
}

void Scene_Play::sEnemySpawner()
{
	
	if (entities.getEntities("Enemy").size() == 0)
	{
		std::shared_ptr<Entity> ina = entities.addEntity("Enemy");
		Animation &inaAnim = GameEngine->assets().getAnimation("InaIdleAnim");
		ina->addComponent<CAnimation>(inaAnim, true);
		ina->addComponent<CTransform>(Vec2(644.0, 480.0), Vec2(0.0, 0.0), Vec2(1.0, 1.0), 0.0);
		ina->addComponent<CBoundingBox>(inaAnim.getSize());
	}
	
}

Vec2 Scene_Play::gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity)
{
	return Vec2(gridX * m_gridSize.x, gridY * m_gridSize.y);
}

void Scene_Play::spawnPlayer()
{
	player = entities.addEntity("Player");
	Animation &playerAnim = GameEngine->assets().getAnimation("PlayerIdleAnim");
	player->addComponent<CAnimation>(playerAnim, true);
	player->addComponent<CTransform>(Vec2(400.0, 480.0), Vec2(0.0, 0.0), Vec2(3.0, 3.0), 0.0);
	player->addComponent<CBoundingBox>(playerAnim.getSize());
	player->addComponent<CInput>();
	player->addComponent<CState>("Idle");
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
				//std::cout << e->tag() << animation.getSprite().getTexture() << "\n";
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
	if (playerV.x * playerV.x == 1 && playerV.y * playerV.y == 1)
	{
		playerV *= 0.5;
	}
	playerV *= playerConfig.S+5.f; // TODO change when actually implemented read config
	if (playerV.dist(Vec2(0.f, 0.f)) > 0.f)
	{
		player->getComponent<CState>().state = "Run";
	}
	else 
	{
		player->getComponent<CState>().state = "Idle";
	}
	// playerV *= PlayerConfig.V;

	pTransform.velocity = playerV;
	pTransform.prevPos = Vec2(pTransform.pos);
	pTransform.pos += pTransform.velocity;
	// player movement based on cInput
	// gravity
	// maximum gravity speed in x y
	// note, set entity's scale.x to -1 to face left
	if (player->getComponent<CState>().facing == "Left")
	{
		// not working.. fix
		pAnimation.setFlipH(true);
		
		//sf::IntRect rect = pAnimation.getSprite().getTextureRect();
		//rect.left = rect.left + rect.width;
		//rect.width *= -1;
		//pAnimation.getSprite().setTextureRect(rect);
	}
	else {
		pAnimation.setFlipH(false);
	}
}

void Scene_Play::sCollision()
{
	// implement Physics::GetOverlap
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
	// complete Animation class
	// set animation based on CState
	// for each entity with animation, call entity->getComponent<CAnimation>().animation.update()
	// if not repeat animation and has ended, destroy entity
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
