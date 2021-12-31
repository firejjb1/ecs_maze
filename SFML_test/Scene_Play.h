#pragma once
#include "Scene.h"

struct PlayerConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V; float S; };

class Scene_Play : public Scene
{
	std::string levelPath;
	std::shared_ptr<Entity> player;
	PlayerConfig playerConfig;
	sf::Text m_gridText;
	Vec2 m_gridSize = { 64, 64 };
	bool m_drawTextures = true;
	bool m_drawCollision = false;
	bool m_drawGrid = true;
	bool m_paused;

	void init();
	void sAnimation();
	void sMovement();
	void sEnemySpawner();
	void sCollision();
	void sLifespan();
	void sRender();
	void sDoAction(const Action&);
	void sDebug();
	void loadLevel(const std::string& levelPath);
	Vec2 gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity);
	void spawnPlayer();
	void onEnd();
	void drawLine(const Vec2& p1, const Vec2& p2);
public:
	void update();
	Scene_Play(std::shared_ptr<Game> g, const std::string & levelPath);

};
