#include "Contact.h"

Contact::Contact(Particle * _p0, Particle * _p1, float _restitution, glm::vec3 _contactNormal, float _penetration, glm::vec3 _contactPoint)
{
	this->m_particle[0] = _p0;
	this->m_particle[1] = _p1;
	this->m_restitution = _restitution;
	this->m_contactNormal = _contactNormal;
	this->m_penetration = _penetration;
	this->m_contactPoint = _contactPoint;
}
Contact::Contact(Particle * _p0, Particle * _p1, float _restitution, glm::vec3 _contactNormal, float _penetration)
{
	this->m_particle[0] = _p0;
	this->m_particle[1] = _p1;
	this->m_restitution = _restitution;
	this->m_contactNormal = _contactNormal;
	this->m_penetration = _penetration;

}
Contact::~Contact()
{
}
void Contact::resolve(float _deltaTs)
{
	resolveVelocity(_deltaTs);
	resolveInterpenetration(_deltaTs);
}
float Contact::calculateSeparatingVelocity()
{
	glm::vec3 relativeVelocity = m_particle[0]->m_velocity;
	if (m_particle[1])
	{
		relativeVelocity -= m_particle[1]->m_velocity;
	}
	return glm::dot(relativeVelocity, m_contactNormal);
}
void Contact::resolveVelocity(float _deltaTs)
{
	//// Find the velocity in the direction of the contact.
	//float separatingVelocity = calculateSeparatingVelocity();
	//// Check whether it needs to be resolved.
	//if (separatingVelocity > 0)
	//{
	//	// The contact is either separating or stationary - there’s
	//	// no impulse required.
	//	return;
	//}
	//// Calculate the new separating velocity.
	//float newSepVelocity = -separatingVelocity * m_restitution;
	//float deltaVelocity = newSepVelocity - separatingVelocity;
	//// We apply the change in velocity to each object in proportion to
	//// its inverse mass (i.e., those with lower inverse mass [higher
	//// actual mass] get less change in velocity).
	//float totalInverseMass = 1/m_particle[0]->m_mass;
	//if (m_particle[1])
	//{
	//	totalInverseMass += 1/m_particle[1]->m_mass;
	//}
	//// If all particles have infinite mass, then impulses have no effect.
	//if (totalInverseMass <= 0) return;
	//// Calculate the impulse to apply.
	//float impulse = deltaVelocity / totalInverseMass;
	//// Find the amount of impulse per unit of inverse mass.
	//glm::vec3 impulsePerIMass =  m_contactNormal * impulse;

	//// Apply impulses: they are applied in the direction of the contact,
	//// and are proportional to the inverse mass.
	//m_particle[0]->m_velocity = (m_particle[0]->m_velocity + impulsePerIMass * (1/m_particle[0]->m_mass));

	//if (m_particle[1])
	//{
	//	// Particle 1 goes in the opposite direction.
	//	m_particle[1]->m_velocity = (m_particle[1]->m_velocity + impulsePerIMass * -(1/m_particle[1]->m_mass));
	//}
//=========================== RESTING contacts ===================
	// Find the velocity in the direction of the contact.
	float separatingVelocity = calculateSeparatingVelocity();
	//cout << "sep: " << separatingVelocity << endl;
	// Check whether it needs to be resolved.
	if (separatingVelocity > 0.0f)
	{
		// The contact is either separating or stationary - there’s
		// no impulse required.
		return;
	}
	// Calculate the new separating velocity.
	float newSepVelocity = -separatingVelocity * m_restitution;
	// Check the velocity build-up due to acceleration only.
	glm::vec3 accCausedVelocity = m_particle[0]->m_acceleration;
	if (m_particle[1]) accCausedVelocity -= m_particle[1]->m_acceleration;
	float accCausedSepVelocity = glm::dot(accCausedVelocity,m_contactNormal) * _deltaTs;
	// If we’ve got a closing velocity due to acceleration build-up,
	// remove it from the new separating velocity.
	if (accCausedSepVelocity < 0)
	{
		newSepVelocity += m_restitution * accCausedSepVelocity;
		// Make sure we haven’t removed more than was
		// there to remove.
		if (newSepVelocity < 0) newSepVelocity = 0;
	}
	float deltaVelocity = newSepVelocity - separatingVelocity;
	// We apply the change in velocity to each object in proportion to
	// its inverse mass (i.e., those with lower inverse mass [higher
	// actual mass] get less change in velocity).
	float totalInverseMass = 1/m_particle[0]->m_mass;
	if (m_particle[1]) totalInverseMass += 1 / m_particle[1]->m_mass;
	// If all particles have infinite mass, then impulses have no effect.
	if (totalInverseMass <= 0) return;
	// Calculate the impulse to apply.
	float impulse = deltaVelocity / totalInverseMass;
	// Find the amount of impulse per unit of inverse mass.
	glm::vec3 impulsePerIMass = m_contactNormal * impulse;
	// Apply impulses: they are applied in the direction of the contact,
	// and are proportional to the inverse mass.
	m_particle[0]->m_velocity = (m_particle[0]->m_velocity + impulsePerIMass * (1/m_particle[0]->m_mass));
	if (m_particle[1])
	{
		// Particle 1 goes in the opposite direction.
		m_particle[1]->m_velocity = (m_particle[1]->m_velocity + impulsePerIMass * -(1/m_particle[1]->m_mass));
	}
}
void Contact::resolveInterpenetration(float _deltaTs)
{
	// If we don’t have any penetration, skip this step.
	if (m_penetration <= 0) return;
	// The movement of each object is based on its inverse mass, so
	// total that.
	float totalInverseMass = 1/m_particle[0]->m_mass;
	if (m_particle[1]) totalInverseMass += 1 / m_particle[1]->m_mass;
	// If all particles have infinite mass, then we do nothing.
	if (totalInverseMass <= 0) return;
	// Find the amount of penetration resolution per unit of inverse mass.
	glm::vec3 movePerIMass = m_contactNormal * (m_penetration / totalInverseMass);
	// Apply the penetration resolution.
	m_particle[0]->m_transform->m_localPosition = (m_particle[0]->m_transform->m_localPosition + movePerIMass * (1 / m_particle[0]->m_mass));
	if (m_particle[1])
	{
		m_particle[1]->m_transform->m_localPosition = (m_particle[1]->m_transform->m_localPosition + movePerIMass * -(1 / m_particle[1]->m_mass));
	}

}

ContactResolver::ContactResolver(float * _deltaTs)
{
	//this->m_iterations = _iterations;
	this->m_deltaTs = _deltaTs;
}
ContactResolver::~ContactResolver()
{

}
void ContactResolver::resolveContacts()
{
	//m_iterationsUsed = 0;
	//while (m_iterationsUsed < m_iterations)
	//{
	//	// Find the contact with the largest closing velocity;
	//	float max = 0;
	//	unsigned maxIndex = _numContacts;
	//	for (unsigned i = 0; i < _numContacts; i++)
	//	{
	//		float sepVel = _contactArray[i].calculateSeparatingVelocity();
	//		if (sepVel < max)
	//		{
	//			max = sepVel;
	//			maxIndex = i;
	//		}
	//	}
	//	// Resolve this contact.
	//	_contactArray[maxIndex].resolve(_deltaTs);
	//	m_iterationsUsed++;
	//}
	for (int i = 0; i < m_contactArray.size();i++)
	{
		m_contactArray[i]->resolve(*m_deltaTs);
		delete m_contactArray[i];
	}
	m_contactArray.clear();
}
void ContactResolver::addContact(Contact * _contact)
{
	m_contactArray.push_back(_contact);
}
