#pragma once
#include "Common.h"
#include "Components.h"

class Entity
{
	friend class EntityManager;

	bool m_active = true;
	size_t m_id = 0;
	std::string m_tag = "default";
	// private constructor. instanced by EntityManager
	Entity(const size_t id, const std::string& tag);

public:
	// component pointers
	ptr<CTransform> cTransform;
	ptr<CShape> cShape;
	ptr<CCollision> cCollision;
	ptr<CInput> cInput;
	ptr<CScore> cScore;
	ptr<CLifespan> cLifespan;


	bool isActive() const;
	const std::string& tag() const;
	const size_t id() const;
	void destroy();
};

