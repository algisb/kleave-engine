#include "Component.h"
#include "Physics.h"

Component::Component(GameObject *_gameObject, string _tag)
{
	this->m_gameObject = _gameObject;
	this->m_tag = _tag;
}
Component::~Component()
{
}

Transform::Transform(GameObject *_gameObject, string _tag, glm::mat4 * _viewMatrix, glm::mat4 * _projectionMatrix) : Component(_gameObject, _tag)
{
	this->m_position = glm::vec3(0 ,0 ,0);
	this->m_rotation = glm::vec3(0, 0, 0);
	this->m_scale = glm::vec3(1, 1, 1);

	this->m_localPosition = glm::vec3(0, 0, 0);
	this->m_localRotation = glm::vec3(0, 0, 0);
	this->m_localScale = glm::vec3(1, 1, 1);

	this->m_localTransform = glm::mat4(1.0f);
	this->m_globalTransform = glm::mat4(1.0f);
	this->m_inheritTransform = glm::mat4(1.0f);
	this->m_parent = NULL;

	this->m_modelMatrix = glm::translate(glm::scale(glm::mat4(1.0f), this->m_scale), this->m_position);
	this->m_rotMatrix = glm::rotate(glm::rotate(glm::rotate(glm::mat4(1.0f), (this->m_rotation.z * 3.14159265358979323846f / 180.0f), glm::vec3(0, 0, 1)), (this->m_rotation.y * 3.14159265358979323846f / 180.0f), glm::vec3(0, 1, 0)), (this->m_rotation.x * 3.14159265358979323846f / 180.0f), glm::vec3(1, 0, 0));
	//this->m_modelMatrix = glm::rotate(glm::rotate(glm::rotate(glm::translate(glm::scale(glm::mat4(1.0f), this->m_scale), this->m_position), (this->m_rotation.z * 3.14159265358979323846f / 180.0f), glm::vec3(0, 0, 1)), (this->m_rotation.y * 3.14159265358979323846f / 180.0f), glm::vec3(0, 1, 0)), (this->m_rotation.x * 3.14159265358979323846f / 180.0f), glm::vec3(1, 0, 0));
	//this->m_rotMatrix = glm::mat4(1.0f);

	this->m_viewMatrix = _viewMatrix;
	this->m_projectionMatrix = _projectionMatrix;
}
void Transform::update()
{
	recalc();
}
void Transform::recalc()
{
	//this->m_modelMatrix = glm::translate(glm::scale(glm::mat4(1.0f), this->m_scale), this->m_position);
	//this->m_rotMatrix = glm::rotate(glm::rotate(glm::rotate(glm::mat4(1.0f), (this->m_rotation.z * 3.14159265358979323846f / 180.0f), glm::vec3(0, 0, 1)), (this->m_rotation.y * 3.14159265358979323846f / 180.0f), glm::vec3(0, 1, 0)), (this->m_rotation.x * 3.14159265358979323846f / 180.0f), glm::vec3(1, 0, 0));
	
	//glm::rotate(glm::rotate(glm::rotate(glm::mat4(1.0f), (this->m_localRotation.z * 3.14159265358979323846f / 180.0f), glm::vec3(0, 0, 1)), (this->m_localRotation.y * 3.14159265358979323846f / 180.0f), glm::vec3(0, 1, 0)), (this->m_localRotation.x * 3.14159265358979323846f / 180.0f), glm::vec3(1, 0, 0));
	
	//this->m_modelMatrix = glm::rotate(glm::rotate(glm::rotate(glm::translate(glm::scale(glm::mat4(1.0f), this->m_scale), this->m_position), (this->m_rotation.z * 3.14159265358979323846f / 180.0f), glm::vec3(0, 0, 1)), (this->m_rotation.y * 3.14159265358979323846f / 180.0f), glm::vec3(0, 1, 0)), (this->m_rotation.x * 3.14159265358979323846f / 180.0f), glm::vec3(1, 0, 0));
	//this->m_rotMatrix = glm::mat4(1.0f);

	
	m_localTransform = glm::mat4(1.0f);
	m_globalTransform = glm::mat4(1.0f);
	m_inheritTransform = glm::mat4(1.0f);
	
	//if parented, add parent's transform
	//m_inheritTransform = glm::translate(glm::rotate(glm::rotate(glm::rotate(glm::mat4(1.0f), (this->m_localRotation.z * 3.14159265358979323846f / 180.0f), glm::vec3(0, 0, 1)), (this->m_localRotation.y * 3.14159265358979323846f / 180.0f), glm::vec3(0, 1, 0)), (this->m_localRotation.x * 3.14159265358979323846f / 180.0f), glm::vec3(1, 0, 0)), this->m_localPosition);
	m_inheritTransform = glm::rotate(glm::rotate(glm::rotate(glm::translate(glm::mat4(1.0f), this->m_localPosition), (this->m_localRotation.z * 3.14159265358979323846f / 180.0f), glm::vec3(0, 0, 1)), (this->m_localRotation.y * 3.14159265358979323846f / 180.0f), glm::vec3(0, 1, 0)), (this->m_localRotation.x * 3.14159265358979323846f / 180.0f), glm::vec3(1, 0, 0));
	m_localTransform = glm::scale(m_inheritTransform, this->m_localScale);

	if (m_parent != NULL)
	{
		m_globalTransform = m_parent->m_inheritTransform*m_localTransform;
		m_inheritTransform = m_parent->m_inheritTransform * m_inheritTransform;
	}
	else
	{
		m_globalTransform = m_localTransform;
	}
	
	

	m_modelMatrix = m_globalTransform;
	m_rotMatrix = glm::mat4(1.0f);

}
void Transform::Parent(Transform * _parent)
{
	//m_children.push_back(_child);
	//_child->m_parent = this;
	this->m_parent = _parent;
	_parent->m_children.push_back(this);

}
Transform::~Transform()
{}

Material::Material(GameObject *_gameObject, string _tag, GLuint * _texture) : Component(_gameObject, _tag)
{
	this->m_texture = _texture;
}
Material::~Material()
{}
void Material::update()
{
}

MeshRenderer::MeshRenderer(GameObject *_gameObject, string _tag, Mesh * _mesh, ShaderProgram * _shaderProgram) : Component(_gameObject, _tag)
{
	this->m_mesh = _mesh;
	this->m_transform = _gameObject->getComponent<Transform>();
	this->m_material = _gameObject->getComponent<Material>();

	this->m_shaderProgram = _shaderProgram;
}
MeshRenderer::~MeshRenderer()
{
}
void MeshRenderer::update()
{
	//_shaderProgram = _shaderProgram3;
	glUseProgram(m_shaderProgram->m_shaderProgramLocation);


		//send texture sampler locations to the shader
		glUniform1i(m_shaderProgram->m_shaderText1SamplerLocation, 0);
		//_modelMatrix = glm::translate(glm::scale(glm::rotate(glm::rotate(glm::rotate(glm::mat4(1.0f), (gameObjects[i]->rotation.z * 3.14159265358979323846f / 180.0f), glm::vec3(0, 0, 1)), (gameObjects[i]->rotation.y * 3.14159265358979323846f / 180.0f), glm::vec3(0, 1, 0)), (gameObjects[i]->rotation.x * 3.14159265358979323846f / 180.0f), glm::vec3(1, 0, 0)), gameObjects[i]->scale), gameObjects[i]->position);
		glUniformMatrix4fv(m_shaderProgram->m_shaderRotMatLocation, 1, GL_FALSE, glm::value_ptr(m_transform->m_rotMatrix));
		glUniformMatrix4fv(m_shaderProgram->m_shaderModelMatLocation, 1, GL_FALSE, glm::value_ptr(m_transform->m_modelMatrix));
		glUniformMatrix4fv(m_shaderProgram->m_shaderViewMatLocation, 1, GL_FALSE, glm::value_ptr(*m_transform->m_viewMatrix));
		glUniformMatrix4fv(m_shaderProgram->m_shaderProjMatLocation, 1, GL_FALSE, glm::value_ptr(*m_transform->m_projectionMatrix));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, *m_material->m_texture);
		

		m_mesh->Draw();

	
}


Camera::Camera(GameObject *_gameObject, string _tag, glm::mat4 _projectionMatrix) : Component(_gameObject, _tag)
{
	this->m_transform = _gameObject->getComponent<Transform>();
	this->m_projectionMatrix = _projectionMatrix;
	m_cameraFront = glm::vec3(
		cos(-m_transform->m_rotation.x) * sin(-m_transform->m_rotation.y),
		sin(m_transform->m_rotation.x),
		cos(-m_transform->m_rotation.x) * cos(-m_transform->m_rotation.y));
}
Camera::~Camera()
{

}

void Camera::update()
{
	//m_viewMatrix = m_transform->m_modelMatrix;
	//m_viewMatrix = glm::rotate(glm::rotate(glm::translate(glm::mat4(1.0f), m_transform->m_position), 0.0f, glm::vec3(1, 0, 0)), m_transform->m_rotation.y, glm::vec3(0, 1, 0));
	//m_viewMatrix = glm::rotate(glm::rotate(glm::rotate(glm::translate(glm::scale(glm::mat4(1.0f), m_transform->m_scale), m_transform->m_position), (m_transform->m_rotation.z * 3.14159265358979323846f / 180.0f), glm::vec3(0, 0, 1)), (m_transform->m_rotation.y * 3.14159265358979323846f / 180.0f), glm::vec3(0, 1, 0)), (m_transform->m_rotation.x * 3.14159265358979323846f / 180.0f), glm::vec3(1, 0, 0));
	//m_viewMatrix = glm::translate(glm::scale(glm::rotate(glm::rotate(glm::rotate(glm::mat4(1.0f), (m_transform->m_rotation.z * 3.14159265358979323846f / 180.0f), glm::vec3(0, 0, 1)), (m_transform->m_rotation.y * 3.14159265358979323846f / 180.0f), glm::vec3(0, 1, 0)), (m_transform->m_rotation.x * 3.14159265358979323846f / 180.0f), glm::vec3(1, 0, 0)), m_transform->m_scale), m_transform->m_position);
	/*m_cameraFront = glm::vec3(
		cos(-m_transform->m_localRotation.x) * sin(-m_transform->m_localRotation.y),
		sin(m_transform->m_localRotation.x),
		cos(-m_transform->m_localRotation.x) * cos(-m_transform->m_localRotation.y));*/
	m_cameraFront = glm::normalize( glm::vec3(0.0f,0.0f,-1.0f) * glm::mat3(m_viewMatrix));

	//m_viewMatrix = glm::lookAt(
	//	m_transform->m_position,           // Camera is here
	//	m_transform->m_position + m_cameraFront, // and looks here : at the same position, plus "direction"
	//	UP                  // Head is up (set to 0,-1,0 to look upside-down)
	//	);


	glm::mat4 tmpMat = m_transform->m_modelMatrix;
	/*tmpMat[3] = -tmpMat[3];
	tmpMat[7] = -tmpMat[7];
	tmpMat[11] = -tmpMat[11];*/
	m_viewMatrix = glm::inverse (tmpMat);
	


}

PhysicsBt::PhysicsBt(GameObject *_gameObject, string _tag, btDiscreteDynamicsWorld * _dynamicsWorld, btCollisionShape* _colliderShape, btScalar _mass) : Component(_gameObject, _tag)
{
	this->m_transform = _gameObject->getComponent<Transform>();
	
	btQuaternion q;
	q.setEulerZYX(m_transform->m_localRotation.z, m_transform->m_localRotation.y, m_transform->m_localRotation.x);
	btDefaultMotionState* fallMotionState = new btDefaultMotionState(btTransform(q, btVector3(m_transform->m_localPosition.x, m_transform->m_localPosition.y, m_transform->m_localPosition.z)));
	
	this->m_dynamicsWorld = _dynamicsWorld;
	this->m_colliderShape = _colliderShape;
	this->m_mass = _mass;
	this->m_inertia = btVector3(0.0f,0.0f,0.0f);
	
	this->m_colliderShape->calculateLocalInertia(this->m_mass,this->m_inertia);

	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(this->m_mass, fallMotionState, this->m_colliderShape, this->m_inertia);

	this->m_rigidBody = new btRigidBody(fallRigidBodyCI);
	this->m_dynamicsWorld->addRigidBody(this->m_rigidBody);

	this->m_rigidBody->activate(true);
	this->m_rigidBody->setActivationState(DISABLE_DEACTIVATION);

}
PhysicsBt::~PhysicsBt()
{
	
}
void PhysicsBt::update()
{
	btTransform trans;
	m_rigidBody->getMotionState()->getWorldTransform(trans);

	

	m_transform->m_localPosition.x = trans.getOrigin().getX();
	m_transform->m_localPosition.y = trans.getOrigin().getY();
	m_transform->m_localPosition.z = trans.getOrigin().getZ();

	glm::quat rotQ;
	rotQ.x = trans.getRotation().getX();
	rotQ.y = trans.getRotation().getY();
	rotQ.z = trans.getRotation().getZ();
	rotQ.w = trans.getRotation().getW();

	glm::vec3 rotEuler = glm::eulerAngles(rotQ)*(180.0f / 3.14159f);
	//cout << "angles: " << rotEuler.x  << " " << rotEuler.y<< " " << rotEuler.z << endl;

	m_transform->m_localRotation.x = rotEuler.x;
	m_transform->m_localRotation.y = rotEuler.y;
	m_transform->m_localRotation.z = rotEuler.z;
	
	//m_colliderShape
	//btQuaternion rot(45,45,45);
	//btQuaternion rot;
	///*rot.setEuler(45.0f, 45.0f, 45.0f);
	//
	//trans.setRotation(rot);*/

	//cout << "quat: " << trans.getRotation().getX() << " " << trans.getRotation().getY() << " " << trans.getRotation().getZ() << endl;

	//glm::quat newRot;
	//newRot.x = trans.getRotation().getX();
	//newRot.y = trans.getRotation().getY();
	//newRot.z = trans.getRotation().getZ();
	//newRot.w = trans.getRotation().getW();

	//glm::vec3 euler = glm::eulerAngles(newRot) * 3.14159f / 180.f;

	//cout << "eul: " << euler.x << " " << euler.y << " " << euler.z << endl;
	//m_transform->m_localRotation = euler;
	//trans.getRotation().setEuler(0.0f,45.0f,0.0f);
	//m_rigidBody->applyTorque(btVector3(0,10,0));



}


//

//Cell * next = NULL;
//
//for (int i = 0; i < 8; i++)
//{
//	if (m_currentCell->m_neighbours[i] != NULL  && m_currentCell->m_neighbours[i]->m_blocked != true)
//	{
//		if (next == NULL)
//		{
//			next = m_currentCell->m_neighbours[i];
//		}
//
//		float currentCost = glm::distance(next->transform->m_position, m_targetCell->transform->m_position);
//		float newCost = glm::distance(m_currentCell->m_neighbours[i]->transform->m_position, m_targetCell->transform->m_position);
//
//		if (newCost < currentCost)
//		{
//			next = m_currentCell->m_neighbours[i];
//		}
//
//	}
//}
//m_currentCell = next;