#pragma once
#include "Component.h"
#include "ShaderManager.h"
#include <sstream>
#include <string>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp> 
#include <gtc/type_ptr.hpp>
using namespace std;
enum LightType{POINT_LIGHT = 0,DIRECTIONAL_LIGHT = 1};
class Light : public Component
{
public:
	
	Transform * m_transform;
	vector<Light*> * m_lights;
	ShaderProgram * m_shaderProgram;

	bool m_enabled;
	glm::vec3 m_lightColour;
	float m_strength;

	//shader locations
	int m_shaderEnabledLocation;
	int m_shaderPositionLocation;
	int m_shaderLightColourLocation;
	int m_shaderStrengthLocation;

	int m_shaderLightTypeLocation;

	int m_shaderNumLightsLocation;
	
	Light(GameObject *_gameObject, string _tag, ShaderProgram * _shaderProgram, vector<Light*> * _lights, bool _enabled, glm::vec3 _lightColour, float _strength);
	virtual ~Light()=0;

	virtual void update()=0;
};

class PointLight : public Light
{
public:
	
	PointLight(GameObject *_gameObject, string _tag, ShaderProgram * _shaderProgram, vector<Light*> * _lights, bool _enabled, glm::vec3 _lightColour, float _strength);
	~PointLight();
	void update();
};

class DirectionalLight : public Light
{
public:
	glm::vec3 m_direction;

	//int m_shaderLightTypeLocation;
	int m_shaderDirectionLocation;
	DirectionalLight(GameObject *_gameObject, string _tag, ShaderProgram * _shaderProgram, vector<Light*> * _lights, bool _enabled, glm::vec3 _lightColour, float _strength, glm::vec3 _direction);
	~DirectionalLight();
	void update();

};
