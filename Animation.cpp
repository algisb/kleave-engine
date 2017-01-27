#include "Animation.h"


JointAnimator::JointAnimator(GameObject *_gameObject, string _tag, Particle * _condition, float _threshold, Transform * _joint0, Transform * _joint1, glm::vec3 _rot0, glm::vec3 _rot1, float * _deltaTs) : Component(_gameObject, _tag)
{
	this->m_condition = _condition;
	this->m_threshold = _threshold;
	this->m_joint0 = _joint0;
	this->m_joint1 = _joint1;
	this->m_rot0 = _rot0;
	this->m_rot1 = _rot1;
	this->m_deltaTs = _deltaTs;
	this->m_timeTs = 0.0f;
}
JointAnimator::~JointAnimator()
{
}
void JointAnimator::update()
{
	float spd = glm::length(glm::vec3(m_condition->m_velocity.x, 0, m_condition->m_velocity.z));
	if (spd > m_threshold)
	{
		float s = sin(m_timeTs*10);
		//cout << spd << endl;
		//cout <<  "s:" << sin(m_timeTs) << endl;
		//cout << "c:" << cos(m_timeTs) << endl;

		m_joint0->m_localRotation = s*m_rot0;
		m_joint1->m_localRotation = -s*m_rot0;
		//cout << "kek" << endl;

	}
	else
	{
		m_joint0->m_localRotation = glm::vec3(0, 0, 0);
		m_joint1->m_localRotation = glm::vec3(0, 0, 0);
	}
	m_timeTs += *m_deltaTs;
}