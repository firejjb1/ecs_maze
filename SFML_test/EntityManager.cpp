#include "EntityManager.h"

EntityManager::EntityManager()
{}

void EntityManager::update()
{
	// remove dead entities
	removeDeadEntities(m_entities);

	for (auto& [tag, entityVec] : m_entityMap)
	{
		removeDeadEntities(entityVec);
	}

	// add new entities
	for (auto entity : m_entitiesToAdd)
	{
		m_entityMap[entity->m_tag].push_back(entity);
		m_entities.push_back(entity);
	}
	m_entitiesToAdd.clear();
}

void EntityManager::removeDeadEntities(EntityVec& vec)
{
	// TODO
}

ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
	auto entity = ptr<Entity>(new Entity(m_totalEntities++, tag));

	m_entitiesToAdd.push_back(entity);

	return entity;
}

const EntityVec& EntityManager::getEntities()
{
	return m_entities;
}

const EntityVec& EntityManager::getEntities(const std::string& tag)
{
	return m_entityMap[tag];
}
