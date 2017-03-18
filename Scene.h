

//#include <Windows.h>
// The GLM library contains vector and matrix functions and classes for us to use
// They are designed to easily work with OpenGL!
#include <glm.hpp> // This is the main GLM header
#include <gtc/matrix_transform.hpp> // This one lets us use matrix transformations
#include <gtc/type_ptr.hpp> // This one gives us access to a utility function which makes sending data to OpenGL nice and easy

#include <fstream>
#include <string>
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <btBulletDynamicsCommon.h>
#include "InputManager.h"
#include "Mesh.h"
#include "GameObject.h"
#include "Component.h"
#include "ShaderManager.h"
#include "Light.h"
#include "EventHandler.h"
#define CAM_SPEED 10.0f

class Scene
{
public:
	unsigned int vertexTotal = 0;
	unsigned int faceTotal = 0;
	Scene(SDL_Window *_window, int _winWidth, int _winHeight, InputManager * _inputManager, EventHandler * _eventHandler);
	~Scene();

	void InputInit();

	void Update(float _deltaTs);
	void Draw();
	

protected:
	//frame time gap
	float deltaTs;
	float particleTs;
	InputManager * inputManager;
	EventHandler * eventHandler;
	//stores all object that are drawn every frame
	vector<GameObject*> gameObjects;
	vector<GameObject*> particles;
	//exclusive gameObject referances (need to be accesses in the update loop)

	GameObject * cube[10];
	GameObject * sphere[10];
	GameObject * plane[10];
	GameObject * empty[10];

	vector<Light*> lightObjects;

	//window setting
	SDL_Window *window;
	int winWidth;
	int winHeight;
	//mouse settings
	int mX;
	int mY;
	glm::vec2 mPosNew;
	glm::vec2 mPosOld;
	//cell which the mouse is hovered over

	//models in scene
	Mesh _cube = Mesh("cube_VT_VN.obj", vertexTotal);
	Mesh _plane = Mesh("plane_VT_VN.obj", vertexTotal);
	Mesh _cylinder = Mesh("cylinder.obj", vertexTotal);
	Mesh _sphere = Mesh("sph.obj", vertexTotal);
	Mesh _particle = Mesh("particle.obj",vertexTotal);
	MeshLine _line;
	MeshPoint _point;
	MeshCircle _circle;





	//camera settigns
	Camera * _mainCam;


	GLuint _texture;//<-------------
	GLuint _texture1;
	GLuint _texture2;
	GLuint _texture3;
	GLuint _texture4;
	GLuint _texture5;
	GLuint _flame;
	GLuint _sky;

	GLuint _baka;


	//shader programs
	ShaderProgram * shaderProgram;
	ShaderProgram * shaderProgramSimple;
	//shader locations

	//bullet physics//////////////////////////////////////////////////
	btBroadphaseInterface* broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;

	btRigidBody* fallRigidBody;
	////////////////////////////////////////////////////////////////////

	//===========================METHODS=======================================
	void LoadTexture(std::string filename, GLuint  &texLocation);
	void LoadTextureA(std::string filename, GLuint  &texLocation);
	void BuildFBO(GLuint &_fbo, GLuint &_texAtt);
	void renderText(GLuint &texLocation, char * message, char * fontFile, SDL_Color color, int fontSize);
	
};
