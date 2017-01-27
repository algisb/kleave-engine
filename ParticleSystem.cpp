#include "ParticleSystem.h"


ParticleSystem::ParticleSystem(GameObject *_gameObject, string _tag) : Component(_gameObject, _tag)
{


}


ParticleSystem::~ParticleSystem()
{
}
void ParticleSystem::update()
{

}

ParticleFX::ParticleFX(GameObject *_gameObject, string _tag, vector<GameObject*> *_gameObjects, float * _deltaTs, float _lifeTime) : Component(_gameObject, _tag)
{
	this->m_deltaTs = _deltaTs;
	this->m_lifeTime = _lifeTime;
	this->m_timeTs = 0;
	this->m_gameObjects = _gameObjects;
}
ParticleFX::~ParticleFX()
{

}
void ParticleFX::update()
{
	m_timeTs += *m_deltaTs;
	if (m_timeTs > m_lifeTime)
	{
		for (int i = 0; i < m_gameObjects->size();i++)
		{

		}
	}
}