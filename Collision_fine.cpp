#include "Collision_fine.h"

Collider::Collider(GameObject * _gameObject, string _tag, glm::mat4 _offset) : Component(_gameObject,  _tag)
{
	this->m_transform = _gameObject->getComponent<Transform>();
	this->m_offset = _offset;
}
Collider::~Collider()
{
}
Sphere::Sphere(GameObject * _gameObject, string _tag, glm::mat4 _offset, float _radius) : Collider(_gameObject, _tag, _offset)
{
	this->m_radius = _radius;
}
Sphere::~Sphere()
{

}
void Sphere::update()
{
	//cout << "sphere" << endl;
}

Plane::Plane(GameObject * _gameObject, string _tag, glm::mat4 _offset) : Collider(_gameObject, _tag, _offset)
{
	this->m_normal = glm::vec3(0,1,0);
}
Plane::~Plane()
{
}
void Plane::update()
{
	m_normal = glm::vec3(0, 1, 0);
	m_normal = glm::normalize( glm::mat3(m_transform->m_globalTransform) * m_normal);
}

Box::Box(GameObject * _gameObject, string _tag, glm::mat4 _offset, glm::vec3 _halfSize) : Collider(_gameObject, _tag, _offset)
{
	this->m_halfSize = _halfSize;
}
Box::~Box()
{

}
void Box::update()
{
	//m_vertex[0] = glm::mat3(m_transform->m_globalTransform)*glm::vec3(-m_halfSize.x, -m_halfSize.y, -m_halfSize.z) + m_transform->m_localPosition;
	//m_vertex[1] = glm::mat3(m_transform->m_globalTransform)*glm::vec3(-m_halfSize.x, -m_halfSize.y, +m_halfSize.z) + m_transform->m_localPosition;
	//m_vertex[2] = glm::mat3(m_transform->m_globalTransform)*glm::vec3(-m_halfSize.x, +m_halfSize.y, -m_halfSize.z) + m_transform->m_localPosition;
	//m_vertex[3] = glm::mat3(m_transform->m_globalTransform)*glm::vec3(-m_halfSize.x, +m_halfSize.y, +m_halfSize.z) + m_transform->m_localPosition;
	//m_vertex[4] = glm::mat3(m_transform->m_globalTransform)*glm::vec3(+m_halfSize.x, -m_halfSize.y, -m_halfSize.z) + m_transform->m_localPosition;
	//m_vertex[5] = glm::mat3(m_transform->m_globalTransform)*glm::vec3(+m_halfSize.x, -m_halfSize.y, +m_halfSize.z) + m_transform->m_localPosition;
	//m_vertex[6] = glm::mat3(m_transform->m_globalTransform)*glm::vec3(+m_halfSize.x, +m_halfSize.y, -m_halfSize.z) + m_transform->m_localPosition;
	//m_vertex[7] = glm::mat3(m_transform->m_globalTransform)*glm::vec3(+m_halfSize.x, +m_halfSize.y, +m_halfSize.z) + m_transform->m_localPosition;
	m_vertex[0] = glm::vec3(m_transform->m_globalTransform*glm::vec4(-m_halfSize.x, -m_halfSize.y, -m_halfSize.z, 1));
	m_vertex[1] = glm::vec3(m_transform->m_globalTransform*glm::vec4(-m_halfSize.x, -m_halfSize.y, +m_halfSize.z, 1));
	m_vertex[2] = glm::vec3(m_transform->m_globalTransform*glm::vec4(-m_halfSize.x, +m_halfSize.y, -m_halfSize.z, 1));
	m_vertex[3] = glm::vec3(m_transform->m_globalTransform*glm::vec4(-m_halfSize.x, +m_halfSize.y, +m_halfSize.z, 1));
	m_vertex[4] = glm::vec3(m_transform->m_globalTransform*glm::vec4(+m_halfSize.x, -m_halfSize.y, -m_halfSize.z, 1));
	m_vertex[5] = glm::vec3(m_transform->m_globalTransform*glm::vec4(+m_halfSize.x, -m_halfSize.y, +m_halfSize.z, 1));
	m_vertex[6] = glm::vec3(m_transform->m_globalTransform*glm::vec4(+m_halfSize.x, +m_halfSize.y, -m_halfSize.z, 1));
	m_vertex[7] = glm::vec3(m_transform->m_globalTransform*glm::vec4(+m_halfSize.x, +m_halfSize.y, +m_halfSize.z, 1));
	/*for (unsigned i = 0; i < 8; i++)
	{
		glm::vec4 v = glm::vec4(m_vertex[i], 1);

		m_vertex[i] = glm::vec3(m_offset * v);
	}*/
}
CollisionResolver::CollisionResolver(ContactResolver * _cr, CollisionCoarse * _cc)
{
	this->m_cr = _cr;
	this->m_cc = _cc;
}
CollisionResolver::~CollisionResolver()
{

}
void CollisionResolver::resolveCollisions()
{
	for (int i = 0; i < m_cc->m_potencialContact.size();i++)
	{
		resolveCollision(m_cc->m_potencialContact[i]->m_p[0], m_cc->m_potencialContact[i]->m_p[1]);
	}
	/*if (m_cr->m_contactArray.size()>0)
	{
		cout << m_cr->m_contactArray.size() << endl;
	}*/
}


void CollisionResolver::resolveCollision(Particle * _p0, Particle * _p1)
{
	if (resolveSphereSphere(_p0, _p1) == true) return;

	if (resolveSpherePlane(_p0,_p1)) return;
	//if (resolveSpherePlane(_p1, _p0)) return;

	if (resolveBoxPlane(_p0, _p1)) return;
	//if (resolveBoxPlane(_p1, _p0)) return;

	
}

bool CollisionResolver::resolveSphereSphere(Particle * _p0, Particle * _p1)
{
	Sphere * s0 = dynamic_cast<Sphere*>(_p0->m_collider);
	Sphere * s1 = dynamic_cast<Sphere*>(_p1->m_collider);
	if (s0 != NULL && s1 != NULL)
	{

		float distanceC2C = glm::length(s0->m_transform->m_localPosition - s1->m_transform->m_localPosition);
		float distanceRpR = s0->m_radius + s1->m_radius;

		if (distanceC2C < distanceRpR) // collision = true
		{
			glm::vec3 normal = glm::normalize(_p0->m_transform->m_localPosition - _p1->m_transform->m_localPosition);
			glm::vec3 midline = _p0->m_transform->m_localPosition - _p0->m_transform->m_localPosition;

			m_cr->addContact(new Contact(_p0, _p1, 0.5f, normal, (distanceRpR - distanceC2C), _p0->m_transform->m_localPosition + midline*0.5f));
			return true;
		}
	}
	return false;
}
bool CollisionResolver::resolveSpherePlane(Particle * _p0, Particle * _p1)
{
	
	Sphere * s0 = dynamic_cast<Sphere*>(_p0->m_collider);
	Plane * p0= dynamic_cast<Plane*>(_p1->m_collider);
	//glm::vec3 
	if (s0 != NULL && p0 != NULL)
	{
		float ballDistance = glm::dot(p0->m_normal, s0->m_transform->m_localPosition) - s0->m_radius;
		// Check for the intersection
		
		if (ballDistance <= glm::length(p0->m_transform->m_localPosition)) //collision = true
		{
			glm::vec3 normal = p0->m_normal;
			m_cr->addContact(new Contact(_p0, NULL, 0.5f, normal, -ballDistance, s0->m_transform->m_localPosition - p0->m_normal * (ballDistance + s0->m_radius)));
			//cout << "Plane" << endl;
			return true;
		}
	}
	return false;
}
bool CollisionResolver::resolveBoxPlane(Particle * _p0, Particle * _p1)
{
	Box * b0 = dynamic_cast<Box*>(_p0->m_collider);
	Plane * p0 = dynamic_cast<Plane*>(_p1->m_collider);
	//glm::vec3 
	if (b0 != NULL && p0 != NULL)
	{
		/*b0->m_vertex[0] = glm::vec3(-b0->m_halfSize.x,- b0->m_halfSize.y, - b0->m_halfSize.z);
		b0->m_vertex[1] = glm::vec3(-b0->m_halfSize.x, - b0->m_halfSize.y, + b0->m_halfSize.z);
		b0->m_vertex[2] = glm::vec3(-b0->m_halfSize.x, + b0->m_halfSize.y, - b0->m_halfSize.z);
		b0->m_vertex[3] = glm::vec3(-b0->m_halfSize.x, + b0->m_halfSize.y, + b0->m_halfSize.z);
		b0->m_vertex[4] = glm::vec3(+b0->m_halfSize.x, - b0->m_halfSize.y, - b0->m_halfSize.z);
		b0->m_vertex[5] = glm::vec3(+b0->m_halfSize.x, - b0->m_halfSize.y, + b0->m_halfSize.z);
		b0->m_vertex[6] = glm::vec3(+b0->m_halfSize.x, + b0->m_halfSize.y, - b0->m_halfSize.z);
		b0->m_vertex[7] = glm::vec3(+b0->m_halfSize.x, + b0->m_halfSize.y, + b0->m_halfSize.z);*/

		for (int i = 0; i < 8; i++)
		{
			// Calculate the distance from the plane.
			float vertexDistance = glm::dot( b0->m_vertex[i] ,p0->m_normal);
			// Compare this to the plane’s distance.
			if (vertexDistance <= glm::length( p0->m_transform->m_localPosition)) //collision = true
			{
				// Create the contact data.
				// The contact point is halfway between the vertex and the
				// plane - we multiply the direction by half the separation
				// distance and add the vertex location.
				/*contact->contactPoint = plane.direction;
				contact->contactPoint *= (vertexDistance - plane.offset);
				contact->contactPoint = vertexPos;
				contact->contactNormal = plane.direction;
				contact->penetration = plane.offset - vertexDistance;*/
				m_cr->addContact(new Contact(_p0,NULL,0.5f,p0->m_normal,glm::length(p0->m_transform->m_localPosition) - vertexDistance,b0->m_vertex[i] ));
			}
		}
		return true;
	}
	return false;
}

