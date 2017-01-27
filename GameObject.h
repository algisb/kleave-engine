#pragma once
#include "glm.hpp"
#include <gtc/matrix_transform.hpp>
#include <typeinfo>
#include "Mesh.h"
#include "Component.h"
class Component;
class GameObject
{

public:
	vector<Component*> m_components;
	bool m_active;
	string m_tag;

	GameObject(string _tag);
	virtual ~GameObject();
	
	void attachComponent(Component * _newComponent);

	template<typename ComponentType> ComponentType * getComponent()
	{
		for (int i = 0; i < this->m_components.size(); i++)
		{
			ComponentType * tempComp = dynamic_cast<ComponentType*>(this->m_components[i]);
			if (tempComp != NULL)
			{
				return tempComp;
			}
		}
		return NULL;
	}
};



