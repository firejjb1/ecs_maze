#pragma once
#include "Scene.h"

struct PlayerConfig { int GX, GY; float CW, CH, SX, SY, SM, GV; std::string B; };
struct EnemyConfig { std::string name; int GX, GY; float CW, CH, SX, SY, SM, GV; };
struct TileConfig { std::string name; int GX, GY; };

class Scene_Play : public Scene
{
	std::string levelPath;
	std::shared_ptr<Entity> player;
	PlayerConfig playerConfig;
	std::vector<EnemyConfig> enemyConfig;
	std::vector<TileConfig> tileConfig;
	sf::Text m_gridText;
	Vec2 m_gridSize;
	Vec2 m_mazeSize;
	bool m_drawTextures = true;
	bool m_drawCollision = false;
	bool m_drawGrid = false;
	bool m_paused;

	void init();
	void sAnimation();
	void sMovement();
	void sEnemySpawner();
	void sCollision();
	void sLifespan();
	void sRender();
	virtual void sDoAction(const Action&);
	void sDebug();
	void loadLevel(const std::string& levelPath);
	Vec2 gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity);
	void spawnPlayer();
	void spawnTiles();
	void spawnTile(float GX, float GY, Vec2 boundingSize, std::string animationName="");
	void onEnd();
	void drawLine(const Vec2& p1, const Vec2& p2);
public:
	void update();
	virtual void doAction(const Action& action);
	Scene_Play(std::shared_ptr<Game> g, const std::string & levelPath);

};
