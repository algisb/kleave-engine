#pragma once
#include "Component.h"
class ParticleSystem : public Component
{
public:
	glm::vec3 m_direction;
	float m_spawnRate;

	ParticleSystem(GameObject *_gameObject, string _tag);
	~ParticleSystem();
	void update();
};

class ParticleFX : public Component
{
public:
	float * m_deltaTs;
	float m_timeTs;
	float m_lifeTime;
	vector<GameObject*> *m_gameObjects;
	ParticleFX(GameObject *_gameObject, string _tag, vector<GameObject*> *_gameObjects, float * _deltaTs, float _lifeTime);
	~ParticleFX();
	void update();
};
