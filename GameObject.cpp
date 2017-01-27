#include "GameObject.h"
#include "glm.hpp"

GameObject::GameObject(string _tag)
{
	this->m_tag = _tag;
	this->m_active = true;
}

GameObject::~GameObject()
{
}

void GameObject::attachComponent(Component * _newComponent)
{
	this->m_components.push_back(_newComponent);
}


