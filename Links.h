#pragma once
#include "Component.h"
#include "Physics.h"
#include "Contact.h"
class Cable : public Component
{
public:

	ContactResolver * m_cr;
	Particle * m_particle[2];

	float m_maxLength;
	float m_restitution;

	Cable(GameObject *_gameObject, string _tag, ContactResolver * _cr, Particle * _p0, Particle * _p1, float _maxLength, float _restitution);
	~Cable();
	void update();
	float currentLength();

};
class CableAnchored : public Component
{
public:

	ContactResolver * m_cr;
	Particle * m_particle;
	glm::vec3 * m_anchor;

	float m_maxLength;
	float m_restitution;

	CableAnchored(GameObject *_gameObject, string _tag, ContactResolver * _cr, Particle * _p0, glm::vec3 * _anchor, float _maxLength, float _restitution);
	~CableAnchored();
	void update();
	float currentLength();

};

class Rod : public Component
{
public:
	ContactResolver * m_cr;
	Particle * m_particle[2];

	float m_length;
	float m_restitution;

	Rod(GameObject *_gameObject, string _tag, ContactResolver * _cr, Particle * _p0, Particle * _p1, float _length, float _restitution);
	~Rod();
	void update();
	float currentLength();
};