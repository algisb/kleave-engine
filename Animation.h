#pragma once
#include <glm.hpp>
#include "Component.h"
#include "Physics.h"

class JointAnimator : public Component
{
public:
	Particle * m_condition;
	float m_threshold;
	Transform * m_joint0;
	Transform * m_joint1;
	glm::vec3 m_rot0;
	glm::vec3 m_rot1;
	float * m_deltaTs;

	float m_timeTs;

	JointAnimator(GameObject *_gameObject, string _tag, Particle * _condition, float _threshold, Transform * _joint0, Transform * _joint1, glm::vec3 _rot0, glm::vec3 _rot1, float * _deltaTs);
	~JointAnimator();
	void update();
};