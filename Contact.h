#pragma once
#include "Physics.h"
class Particle;
class Contact
{
public:
	Particle * m_particle[2];

	float m_restitution;

	glm::vec3 m_contactNormal;
	glm::vec3 m_contactPoint;

	float m_penetration;
	Contact(Particle * _p0, Particle * _p1, float _restitution, glm::vec3 _contactNormal, float _penetration, glm::vec3 _contactPoint);
	Contact(Particle * _p0 , Particle * _p1 , float _restitution, glm::vec3 _contactNormal, float _penetration);
	~Contact();

	void resolve(float _deltaTs);
	float calculateSeparatingVelocity();

	void resolveVelocity(float _deltaTs);
	void resolveInterpenetration(float _deltaTs);
};
class ContactResolver
{
public:

	//unsigned int m_iterations;
	//unsigned m_iterationsUsed;
	float * m_deltaTs;
	vector<Contact*> m_contactArray;

	ContactResolver(float * _deltaTs);
	~ContactResolver();
	void resolveContacts();
	void addContact(Contact * _contact);
};