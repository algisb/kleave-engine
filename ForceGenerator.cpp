#include "ForceGenerator.h"



GravityFG::GravityFG(glm::vec3 _g)
{
	this->m_g = _g;
}
GravityFG::~GravityFG()
{

}
void GravityFG::updateForce(Particle *_particle, float _deltaTs)
{
	if (1 / _particle->m_mass >= 0.0f)
	{
		glm::vec3 force = _particle->m_mass*m_g;
		//cout << "weight: " << glm::length(force) << endl;
		_particle->applyForce(force);
	}
}

DragFG::DragFG(float _dragK1, float _dragK2)
{
	this->m_dragK1 = _dragK1;
	this->m_dragK2 = _dragK2;
}
DragFG::~DragFG()
{

}
void DragFG::updateForce(Particle *_particle, float _deltaTs)
{
	glm::vec3 v = _particle->m_velocity;
	glm::vec3 vn = glm::normalize(_particle->m_velocity);
	float vMag = glm::length(v);
	
	if (vMag > 0.0f)
	{
		glm::vec3 force = -vn*(m_dragK1*vMag + m_dragK2* vMag*vMag);
		//glm::vec3 force = -glm::v;
		//cout << "drag force: " << glm::length(force) << endl;
		//if (glm::length(_particle->m_acceleration) != 0.0f)
		//{
			_particle->applyForce(force);
		//}
	}

	
}

SpringFG::SpringFG(Particle * _other, float _springConstant, float _restLength, bool _push, bool _pull)
{
	this->m_other = _other;
	this->m_springConstant = _springConstant;
	this->m_restLength = _restLength;
	this->m_push = _push;
	this->m_pull = _pull;
}
SpringFG::~SpringFG()
{

}
void SpringFG::updateForce(Particle *_particle, float _deltaTs)
{
	//cout << m_other->m_transform->m_localPosition.y << endl;
	// Calculate the vector of the spring.
	glm::vec3 force = _particle->m_transform->m_localPosition;

	force -= m_other->m_transform->m_localPosition;
	// Calculate the magnitude of the force.
	float magnitude = glm::length(force);

	if (m_push != true || m_pull != true)
	{
		if (m_push == true)
		{
			if (magnitude >= m_restLength) return;
		}
		if (m_pull == true)
		{
			if (magnitude <= m_restLength) return;
		}
	}
	magnitude = (magnitude - m_restLength); //magnitude = glm::abs(magnitude - m_restLength);
	magnitude *= m_springConstant;
	// Calculate the final force and apply it.
	force = glm::normalize(force);
	force *= -magnitude;


	_particle->applyForce(force);
	//cout << "v: " << glm::length(_particle->m_velocity) << endl;
}

AnchoredSpringFG::AnchoredSpringFG(glm::vec3 _anchor, float _springConstant, float _restLength, bool _push, bool _pull)
{
	this->m_anchor = _anchor;
	this->m_springConstant = _springConstant;
	this->m_restLength = _restLength;
	this->m_push = _push;
	this->m_pull = _pull;
}
AnchoredSpringFG::~AnchoredSpringFG()
{

}
void AnchoredSpringFG::updateForce(Particle *_particle, float _deltaTs)
{
	//cout << m_other->m_transform->m_localPosition.y << endl;
	// Calculate the vector of the spring.
	glm::vec3 force = _particle->m_transform->m_localPosition;

	force -= m_anchor;
	// Calculate the magnitude of the force.
	float magnitude = glm::length(force);
	if (m_push != true || m_pull != true)
	{
		if (m_push == true)
		{
			if (magnitude >= m_restLength) return;
		}
		if (m_pull == true)
		{
			if (magnitude <= m_restLength) return;
		}
	}
	magnitude = (magnitude - m_restLength); //magnitude = glm::abs(magnitude - m_restLength);
	magnitude *= m_springConstant;
	// Calculate the final force and apply it.
	force = glm::normalize(force);
	force *= -magnitude;
	_particle->applyForce(force);
}

FrictionFG::FrictionFG(float _friction)
{
	this->m_friction = _friction;
}

FrictionFG::~FrictionFG()
{
}
void FrictionFG::updateForce(Particle *_particle, float _deltaTs)
{
	glm::vec3 tmpV = _particle->m_velocity* glm::pow(m_friction, _deltaTs);
	tmpV.y = _particle->m_velocity.y;
	_particle->m_velocity = tmpV;
}

