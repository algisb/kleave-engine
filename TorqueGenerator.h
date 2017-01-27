#pragma once
#include"Physics.h"
class Particle;
class TorqueGenerator
{
public:
	virtual void updateForce(Particle *_particle, float _deltaTs) = 0;
};

