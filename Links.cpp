#include "Links.h"


Cable::Cable(GameObject *_gameObject, string _tag, ContactResolver * _cr, Particle * _p0, Particle * _p1, float _maxLength, float _restitution) : Component(_gameObject, _tag)
{
	this->m_cr = _cr;
	this->m_particle[0] = _p0;
	this->m_particle[1] = _p1;
	this->m_maxLength = _maxLength;
	this->m_restitution = _restitution;
}
Cable::~Cable()
{

}
void Cable::update()
{
	// Find the length of the cable.
	float length = currentLength();
	// Check whether we’re overextended.
	if (length < m_maxLength)
	{
		return;
	}
	// Calculate the normal.
	glm::vec3 normal = glm::normalize( m_particle[1]->m_transform->m_localPosition - m_particle[0]->m_transform->m_localPosition);
	m_cr->addContact(new Contact(m_particle[0], m_particle[1], m_restitution, normal, (length - m_maxLength)));

}
float Cable::currentLength()
{
	glm::vec3 relativePos = m_particle[0]->m_transform->m_localPosition - m_particle[1]->m_transform->m_localPosition;
	return glm::length(relativePos);
}

CableAnchored::CableAnchored(GameObject *_gameObject, string _tag, ContactResolver * _cr, Particle * _p0, glm::vec3 * _anchor, float _maxLength, float _restitution) : Component(_gameObject, _tag)
{
	this->m_cr = _cr;
	this->m_particle = _p0;
	this->m_anchor = _anchor;
	this->m_maxLength = _maxLength;
	this->m_restitution = _restitution;
}
CableAnchored::~CableAnchored()
{

}
void CableAnchored::update()
{
	// Find the length of the cable.
	float length = currentLength();
	// Check whether we’re overextended.
	if (length < m_maxLength)
	{
		return;
	}
	// Calculate the normal.
	glm::vec3 normal = glm::normalize(m_particle->m_transform->m_localPosition - *m_anchor);
	m_cr->addContact(new Contact(m_particle, NULL, m_restitution, -normal, (length - m_maxLength)));

}
float CableAnchored::currentLength()
{
	glm::vec3 relativePos = m_particle->m_transform->m_localPosition - *m_anchor;
	return glm::length(relativePos);
}


Rod::Rod(GameObject *_gameObject, string _tag, ContactResolver * _cr, Particle * _p0, Particle * _p1, float _length, float _restitution) : Component(_gameObject, _tag)
{
	this->m_cr = _cr;
	this->m_particle[0] = _p0;
	this->m_particle[1] = _p1;
	this->m_length = _length;
	this->m_restitution = _restitution;
}
Rod::~Rod()
{

}
void Rod::update()
{
	// Find the length of the cable.
	float cLength = currentLength();
	// Check whether we’re overextended.
	// Calculate the normal.
	if (cLength == m_length)
	{
		return;
	}

	glm::vec3 normal = glm::normalize(m_particle[1]->m_transform->m_localPosition - m_particle[0]->m_transform->m_localPosition);

	if (cLength > m_length)
	{
		m_cr->addContact(new Contact(m_particle[0], m_particle[1], m_restitution, normal, (cLength - m_length)));
	}
	else
	{
		m_cr->addContact(new Contact(m_particle[0], m_particle[1], m_restitution, normal * -1.0f, (m_length - cLength)));
	}
}
float Rod::currentLength()
{
	glm::vec3 relativePos = m_particle[0]->m_transform->m_localPosition - m_particle[1]->m_transform->m_localPosition;
	return glm::length(relativePos);
}