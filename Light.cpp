#include "Light.h"


Light::Light(GameObject *_gameObject, string _tag, ShaderProgram * _shaderProgram, vector<Light*> * _lights, bool _enabled, glm::vec3 _lightColour, float _strength) : Component(_gameObject, _tag)
{
	this->m_transform = _gameObject->getComponent<Transform>();
	this->m_shaderProgram = _shaderProgram;
	this->m_lights = _lights;

	this->m_enabled = _enabled;
	this->m_lightColour = _lightColour;
	this->m_strength = _strength;

	stringstream ss;
	ss << m_lights->size();
	string loc;
	ss >> loc;
	
	string nameInShader = "light[" + loc + "].enabled";
	glUseProgram(m_shaderProgram->m_shaderProgramLocation);
	//cout << "loc: " << nameInShader << endl;
	this->m_shaderEnabledLocation = glGetUniformLocation(m_shaderProgram->m_shaderProgramLocation, nameInShader.c_str());

	nameInShader.clear();
	nameInShader = "light[" + loc + "].position";
	this->m_shaderPositionLocation = glGetUniformLocation(m_shaderProgram->m_shaderProgramLocation, nameInShader.c_str());

	nameInShader.clear();
	nameInShader = "light[" + loc + "].lightColour";
	this->m_shaderLightColourLocation = glGetUniformLocation(m_shaderProgram->m_shaderProgramLocation, nameInShader.c_str());

	nameInShader.clear();
	nameInShader = "light[" + loc + "].strength";
	this->m_shaderStrengthLocation = glGetUniformLocation(m_shaderProgram->m_shaderProgramLocation, nameInShader.c_str());

	nameInShader.clear();
	nameInShader = "light[" + loc + "].lightType";
	this->m_shaderLightTypeLocation = glGetUniformLocation(m_shaderProgram->m_shaderProgramLocation, nameInShader.c_str());
	
	this->m_shaderNumLightsLocation = glGetUniformLocation(m_shaderProgram->m_shaderProgramLocation, "numLights");
	//glUniform1i(m_shaderNumLightsLocation, m_lights->size());

	//glUniform1i(m_shaderEnabledLocation, 1);//bool
	//glUniform3fv(m_shaderPositionLocation, 1, glm::value_ptr(glm::vec3(*m_transform->m_viewMatrix * m_transform->m_modelMatrix * m_transform->m_rotMatrix * glm::vec4(0, 0, 0, 1)))); // << todo
	//glUniform3f(m_shaderLightColourLocation, m_lightColour.x, m_lightColour.y, m_lightColour.z);
	//glUniform1f(m_shaderStrengthLocation, m_strength);
	//glUseProgram(0);

}
Light::~Light()
{
}
void Light::update()
{
	//cout << m_lights->size() << endl;
	//glUseProgram(m_shaderProgram->m_shaderProgramLocation);

	//glUniform1i(m_shaderNumLightsLocation, m_lights->size());
	//glUniform1i(m_shaderEnabledLocation, 1);//bool
	//glUniform3fv(m_shaderPositionLocation, 1, glm::value_ptr(glm::vec3(*m_transform->m_viewMatrix * m_transform->m_modelMatrix * m_transform->m_rotMatrix * glm::vec4(0, 0, 0, 1)))); // << todo
	//glUniform3f(m_shaderLightColourLocation, m_lightColour.x, m_lightColour.y, m_lightColour.z);
	//glUniform1f(m_shaderStrengthLocation, m_strength);
	//glUseProgram(0);

}

PointLight::PointLight(GameObject *_gameObject, string _tag, ShaderProgram * _shaderProgram, vector<Light*> * _lights, bool _enabled, glm::vec3 _lightColour, float _strength) : Light(_gameObject, _tag,  _shaderProgram, _lights, _enabled, _lightColour, _strength)
{
	/*stringstream ss;
	ss << m_lights->size();
	string loc;
	ss >> loc;

	string nameInShader = "light[" + loc + "].lightType";
	glUseProgram(m_shaderProgram->m_shaderProgramLocation);
	this->m_shaderLightTypeLocation = glGetUniformLocation(m_shaderProgram->m_shaderProgramLocation, nameInShader.c_str());*/
}
PointLight::~PointLight()
{

}
void PointLight::update()
{
	glUseProgram(m_shaderProgram->m_shaderProgramLocation);

	glUniform1i(m_shaderNumLightsLocation, m_lights->size());
	glUniform1i(m_shaderEnabledLocation, 1);//bool
	glUniform3fv(m_shaderPositionLocation, 1, glm::value_ptr(glm::vec3(*m_transform->m_viewMatrix * m_transform->m_modelMatrix * m_transform->m_rotMatrix * glm::vec4(0, 0, 0, 1)))); // << todo
	glUniform3f(m_shaderLightColourLocation, m_lightColour.x, m_lightColour.y, m_lightColour.z);
	glUniform1f(m_shaderStrengthLocation, m_strength);

	glUniform1i(m_shaderLightTypeLocation, POINT_LIGHT);
}

DirectionalLight::DirectionalLight(GameObject *_gameObject, string _tag, ShaderProgram * _shaderProgram, vector<Light*> * _lights, bool _enabled, glm::vec3 _lightColour, float _strength, glm::vec3 _direction) : Light(_gameObject, _tag, _shaderProgram, _lights, _enabled, _lightColour, _strength)
{
	m_direction = _direction;
	stringstream ss;
	ss << m_lights->size();
	string loc;
	ss >> loc;

	//string nameInShader = "light[" + loc + "].lightType";
	//glUseProgram(m_shaderProgram->m_shaderProgramLocation);
	//this->m_shaderLightTypeLocation = glGetUniformLocation(m_shaderProgram->m_shaderProgramLocation, nameInShader.c_str());

	
	string nameInShader = "light[" + loc + "].lightDirection";
	this->m_shaderDirectionLocation = glGetUniformLocation(m_shaderProgram->m_shaderProgramLocation, nameInShader.c_str());

}
DirectionalLight::~DirectionalLight()
{
}
void DirectionalLight::update()
{
	glUseProgram(m_shaderProgram->m_shaderProgramLocation);

	glUniform1i(m_shaderNumLightsLocation, m_lights->size());
	glUniform1i(m_shaderEnabledLocation, 1);//bool
	glUniform3fv(m_shaderPositionLocation, 1, glm::value_ptr(glm::vec3(*m_transform->m_viewMatrix * m_transform->m_modelMatrix * m_transform->m_rotMatrix * glm::vec4(0, 0, 0, 1)))); // << todo
	glUniform3f(m_shaderLightColourLocation, m_lightColour.x, m_lightColour.y, m_lightColour.z);
	glUniform1f(m_shaderStrengthLocation, m_strength);

	glUniform1i(m_shaderLightTypeLocation, DIRECTIONAL_LIGHT);
	
	glUniform3fv(m_shaderDirectionLocation, 1, glm::value_ptr(glm::normalize(glm::mat3(*m_transform->m_viewMatrix)*glm::normalize(m_direction))));
}