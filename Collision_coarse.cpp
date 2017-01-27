#include "Collision_coarse.h"
PotentialContact::PotentialContact(Particle * _p0, Particle * _p1)
{
	this->m_p[0] = _p0;
	this->m_p[1] = _p1;
}

PotentialContact::~PotentialContact()
{

}


CollisionCoarse::CollisionCoarse()
{

}
CollisionCoarse::~CollisionCoarse()
{

}
void CollisionCoarse::checkforCollision()
{
	for (int i = 0; i < m_potencialContact.size(); i++)
	{
		delete m_potencialContact[i];
	}
	m_potencialContact.clear();
	for (int i = 0; i < m_sphereBV.size(); i++)
	{
		for (int j = 0; j < m_sphereBV.size(); j++)
		{
			if (m_sphereBV[i] != m_sphereBV[j])
			{
				if (m_sphereBV[i]->overlaps(m_sphereBV[j]) == true)
				{
					addPotentialContact(new PotentialContact(m_sphereBV[i]->m_gameObject->getComponent<Particle>(), m_sphereBV[j]->m_gameObject->getComponent<Particle>()));
				}
			}
		}

	}
}
void CollisionCoarse::addPotentialContact(PotentialContact * _pc)
{
	m_potencialContact.push_back(_pc);
}

SphereBV::SphereBV(GameObject * _gameObject, string _tag, CollisionCoarse * _collisionCoarse, float _defaultRadius) : Component(_gameObject, _tag)
{
	this->m_transform = _gameObject->getComponent<Transform>();
	this->m_collisionCoarse = _collisionCoarse;
	m_collisionCoarse->m_sphereBV.push_back(this);
	this->m_defaultRadius = _defaultRadius;
}
SphereBV::~SphereBV()
{

}
void SphereBV::update()
{
	float maxScale = 0;
	for (int i = 0; i < 3; i++)
	{
		if (m_transform->m_localScale[i]> maxScale)
		{
			maxScale = m_transform->m_localScale[i];
		}
	}
	m_radius = m_defaultRadius * maxScale;

	m_center = glm::vec3(m_transform->m_globalTransform * glm::vec4(0, 0, 0, 1));

}

bool SphereBV::overlaps(SphereBV * _other)
{
	float distanceC2C = glm::length(m_center - _other->m_center);

	if (distanceC2C < (m_radius + _other->m_radius))
	{
		return true;
	}
	else
	{
		return false;
	}
}
