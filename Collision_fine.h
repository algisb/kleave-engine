#pragma once
#include <glm.hpp>
#include "Component.h"
#include "Physics.h"
#include "Contact.h"
#include "Collision_coarse.h"
class CollisionCoarse;
class ContactResolver;

class Collider : public Component
{
public:
	Transform * m_transform;
	glm::mat4 m_offset;
	Collider(GameObject * _gameObject, string _tag, glm::mat4 _offset);
	virtual ~Collider() = 0;
	virtual void update() = 0;

	
};
class Sphere : public Collider
{
public:
	float m_radius;
	Sphere(GameObject * _gameObject, string _tag, glm::mat4 _offset, float _radius);
	~Sphere();
	void update();
	
};
class Plane : public Collider
{
public:
	Plane(GameObject * _gameObject, string _tag, glm::mat4 _offset);
	~Plane();
	void update();

	glm::vec3 m_normal;
	//float m_offset;
};
class Box : public Collider
{
public:
	glm::vec3 m_vertex[8];
	glm::vec3 m_halfSize;

	Box(GameObject * _gameObject, string _tag, glm::mat4 _offset, glm::vec3 _halfSize);
	~Box();
	void update();

};

class CollisionResolver
{
public:
	ContactResolver * m_cr; // generate a contact if there is a collision
	CollisionCoarse * m_cc; // get particles that are likely to intersect

	CollisionResolver(ContactResolver * _cr, CollisionCoarse * m_cc);
	~CollisionResolver();
	//loop through all potencial contacts
	void resolveCollisions();


private:
	//resolve collision depending on the type
	void resolveCollision(Particle * _p0, Particle * _p1);
	//specific type resolves
	bool resolveSphereSphere(Particle * _p0, Particle * _p1);
	bool resolveSpherePlane(Particle * _p0, Particle * _p1);
	bool resolveBoxPlane(Particle * _p0, Particle * _p1);
	

};

