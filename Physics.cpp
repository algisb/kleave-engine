#include "Physics.h"


Particle::Particle(GameObject *_gameObject, string _tag, float * _deltaTs, float _damping, float _angularDamping, float _mass) : Component(_gameObject, _tag)
{
	this->deltaTs = _deltaTs;
	//this->m_g = _g;
	this->m_transform = _gameObject->getComponent<Transform>();
	this->m_collider = _gameObject->getComponent<Collider>();
	this->m_velocity = glm::vec3(0,0,0);
	this->m_acceleration = glm::vec3(0,0.0f,0);
	this->m_damping = _damping;
	this->m_angularDamping = _angularDamping;
	this->m_mass = _mass;
	this->m_forceAccum = glm::vec3(0,0,0);

	this->m_angularVelocity = glm::vec3(0, 0, 0);
	this->m_angularAcceleration = glm::vec3(0, 0, 0);
	this->m_inverseInertiaTensor = glm::mat3(glm::vec3((m_mass*(m_transform->m_localScale.y*m_transform->m_localScale.y + m_transform->m_localScale.z*m_transform->m_localScale.z))/12, 0, 0),
											 glm::vec3(0, (m_mass*(m_transform->m_localScale.x*m_transform->m_localScale.x + m_transform->m_localScale.z*m_transform->m_localScale.z)) / 12, 0),
											 glm::vec3(0, 0, (m_mass*(m_transform->m_localScale.x*m_transform->m_localScale.x + m_transform->m_localScale.y*m_transform->m_localScale.y)) / 12)
											 );
	this->m_inverseInertiaTensor = glm::inverse(m_inverseInertiaTensor);
}
Particle::~Particle()
{

}
void Particle::update()
{
	//applyForce(m_mass * m_g * *deltaTs); //add gravitational force
	for (int i = 0; i < m_forceGenerators.size();i++)
	{
		m_forceGenerators[i]->updateForce(this, *deltaTs);
	}
	integrate();
	integrateAngle();
}
void Particle::integrate()
{
	if (1/m_mass <= 0.0f) return;
	m_transform->m_localPosition += m_velocity * *deltaTs; //position

	//m_acceleration += m_forceAccum * (1 / m_mass); //acceleration

	glm::vec3 resultingAcc = m_acceleration;
	resultingAcc += (m_forceAccum / m_mass);

	m_velocity += resultingAcc * *deltaTs; //velocity

	m_velocity *= glm::pow(m_damping, *deltaTs); //damping
	//cout << "v: " << m_velocity.y << endl;
	//cout << "a: " << m_acceleration.y << endl;
	//cout << "F: " << m_forceAccum.y << endl;
	m_forceAccum = glm::vec3(0, 0, 0);

	


}
void Particle::applyForce(glm::vec3 _force)
{
	//f = ma
	//a = f / m
	m_forceAccum += _force;
}
void Particle::addForceGenerator(ForceGenerator * _forceGenerator)
{
	m_forceGenerators.push_back(_forceGenerator);
}
void Particle::integrateAngle()
{
	if (1 / m_mass <= 0.0f) return;
	m_transform->m_localRotation += m_angularVelocity * *deltaTs; //position

	glm::vec3 resultingAnglularAcc = m_angularAcceleration;
	resultingAnglularAcc += m_torqueAccum * m_inverseInertiaTensor;

	m_angularVelocity += resultingAnglularAcc * *deltaTs; //velocity


	m_angularVelocity *= glm::pow(m_angularDamping, *deltaTs); //damping
	m_torqueAccum = glm::vec3(0, 0, 0);
}
void Particle::applyTorque(glm::vec3 _torque)
{
	m_torqueAccum += _torque;
}
