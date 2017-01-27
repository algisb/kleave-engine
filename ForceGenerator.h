#pragma once
#include"Physics.h"
class Particle;
//force generators apply force every frame
class ForceGenerator
{
public:
	virtual void updateForce(Particle *_particle, float _deltaTs) = 0;
};

class GravityFG : public ForceGenerator
{
public:
	glm::vec3 m_g;
	GravityFG(glm::vec3 _g);
	~GravityFG();
	void updateForce(Particle *_particle, float _deltaTs);
};

class DragFG : public ForceGenerator
{
public:
	float m_dragK1;
	float m_dragK2;
	DragFG(float _dragK1, float _dragK2);
	~DragFG();
	void updateForce(Particle *_particle, float _deltaTs);
};

class SpringFG : public ForceGenerator
{
public:
	Particle *m_other;

	float m_springConstant;

	float m_restLength;

	bool m_push;
	bool m_pull;

	SpringFG(Particle * _other, float _springConstant, float _restLength, bool _push, bool _pull);
	~SpringFG();
	
	void updateForce(Particle *_particle, float _deltaTs);
};

class AnchoredSpringFG : public ForceGenerator
{
public:
	glm::vec3 m_anchor;

	float m_springConstant;

	float m_restLength;

	bool m_push;
	bool m_pull;

	AnchoredSpringFG(glm::vec3 _anchor, float _springConstant, float _restLength, bool _push, bool _pull);
	~AnchoredSpringFG();

	void updateForce(Particle *_particle, float _deltaTs);

};

//does not affect y axis
class FrictionFG : public ForceGenerator
{
public:
	float m_friction; // 0.0f - 1.0f <-- 1 being frictionless 
	FrictionFG(float _friction);
	~FrictionFG();
	void updateForce(Particle *_particle, float _deltaTs);


};

