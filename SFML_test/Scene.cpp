#include "Scene.h"

void Scene::doAction(Action action)
{
	sDoAction(action);
}

void Scene::registerAction(int i, std::string a)
{
	actionMap[i] = a;
}

Scene::Scene(std::shared_ptr<Game> g)
	:GameEngine{g}
{}

void Scene::simulate(int i)
{

}