#pragma once
#include "GameObject.h"
#include "Mesh.h"
#include <time.h>
#include <gtc/type_ptr.hpp> 
#include <glm.hpp>
#include <quaternion.hpp>
#include "ShaderManager.h"
#include "SETTINGS.h"
#include <btBulletDynamicsCommon.h>
//

class GameObject;
class Component
{
public:
	GameObject * m_gameObject;
	string m_tag;

	Component(GameObject *_gameObject, string _tag);
	virtual ~Component()=0;
	virtual void update()=0;
};

class Transform : public Component
{
	public:
		// world space
		glm::vec3 m_position; 
		glm::vec3 m_rotation;
		glm::vec3 m_scale;

		//relative to parent
		glm::vec3 m_localPosition;
		glm::vec3 m_localRotation;
		glm::vec3 m_localScale;


		glm::mat4 m_rotMatrix;
		glm::mat4 m_modelMatrix;

		glm::mat4 *m_viewMatrix;
		glm::mat4 *m_projectionMatrix;

		//new scene graph
		glm::mat4 m_globalTransform;
		glm::mat4 m_localTransform;
		glm::mat4 m_inheritTransform;
		Transform * m_parent;
		vector<Transform*> m_children;


		Transform(GameObject *_gameObject, string _tag, glm::mat4 * _viewMatrix, glm::mat4 * _projectionMatrix );
		~Transform();
		void update();
		void recalc();

		void Parent(Transform * _parent);
		//void RemoveChild(ActorID id);

};
class Material : public Component
{
public:
	GLuint * m_texture;
	Material(GameObject *_gameObject, string _tag, GLuint * _texture);
	~Material();
	void update();
};
class MeshRenderer : public Component
{
public:
	Mesh * m_mesh;
	Transform * m_transform;
	Material * m_material;
	ShaderProgram * m_shaderProgram;

	MeshRenderer(GameObject *_gameObject, string _tag, Mesh * _mesh, ShaderProgram * _shaderProgram);
	~MeshRenderer();
	void update();

};
class Camera : public Component
{
public:
	Transform * m_transform;
	glm::vec3 m_cameraFront;
	glm::mat4 m_projectionMatrix;
	glm::mat4 m_viewMatrix;

	Camera(GameObject *_gameObject, string _tag, glm::mat4 _projectionMatrix);
	~Camera();
	void update();
};

class PhysicsBt : public Component
{
public:
	Transform * m_transform;

	btDiscreteDynamicsWorld * m_dynamicsWorld;

	btCollisionShape* m_colliderShape;
	btDefaultMotionState* m_defaultMotionState;

	btScalar m_mass;
	btVector3 m_inertia;
	btRigidBody * m_rigidBody;

	PhysicsBt(GameObject *_gameObject, string _tag, btDiscreteDynamicsWorld * _dynamicsWorld, btCollisionShape* _colliderShape, btScalar _mass);
	~PhysicsBt();
	void update();
};

