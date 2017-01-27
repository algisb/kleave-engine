#pragma once
#include "Component.h"

#include <gtc/type_ptr.hpp> 
#include <glm.hpp>
#include "Mesh.h"
#include "Physics.h"
class Particle;
class PotentialContact
{
public:
	PotentialContact(Particle * _p0, Particle * _p1);
	~PotentialContact();
	Particle * m_p[2];
};
class SphereBV;
class CollisionCoarse
{
public:
	vector<SphereBV*> m_sphereBV;
	vector<PotentialContact*> m_potencialContact;

	CollisionCoarse();
	~CollisionCoarse();
	void checkforCollision();
	void addPotentialContact(PotentialContact * _pc);

};
class SphereBV : public Component
{
public:
	Transform * m_transform;
	glm::vec3 m_center;
	float m_radius;

	float m_defaultRadius; //cant fit the shape when the scale is (1,1,1)
	CollisionCoarse * m_collisionCoarse;
	SphereBV(GameObject * _gameObject, string _tag, CollisionCoarse * _collisionCoarse, float _defaultRadius);
	~SphereBV();
	void update();
	bool overlaps(SphereBV * _other);

};
