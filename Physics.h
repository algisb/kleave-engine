#pragma once
#include "Component.h"
#include "ForceGenerator.h"
#include "Collision_fine.h"
class Collider;
class ForceGenerator;
//simplest physics component
class Particle : public Component 
{
public:
	float * deltaTs;
	//glm::vec3 m_g;
	Transform * m_transform;
	Collider * m_collider;
	//linear motion
	glm::vec3 m_velocity;
	glm::vec3 m_acceleration;
	float m_damping;
	float m_mass;
	glm::vec3 m_forceAccum;
	vector<ForceGenerator*> m_forceGenerators;

	//angular motion
	glm::vec3 m_angularVelocity;
	glm::vec3 m_angularAcceleration;

	float m_angularDamping;

	glm::vec3 m_torqueAccum;
	glm::mat3 m_inverseInertiaTensor;

	Particle(GameObject *_gameObject, string _tag, float * _deltaTs, float _damping, float _angularDamping, float _mass);
	~Particle();
	void update();
	//linear motion
	void integrate();
	void applyForce(glm::vec3 _force);
	void addForceGenerator(ForceGenerator * _forceGenerator);
	//angular motion
	void integrateAngle();
	void applyTorque(glm::vec3 _torque);
};


