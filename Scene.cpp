
#include "Scene.h"
#include <iostream>
#include "SETTINGS.h"

Scene::Scene(SDL_Window *_window, int _winWidth, int _winHeight, InputManager * _inputManager, EventHandler * _eventHandler)
{
	
	this->window = _window; 
	this->winWidth = _winWidth;
	this->winHeight = _winHeight;
	this->inputManager = _inputManager;
	this->eventHandler = _eventHandler;
    /////////////////Meshes and textures////////////////////////
    _cube       = new Mesh("cube_VT_VN.obj", vertexTotal);
    _plane      = new Mesh("plane_VT_VN.obj", vertexTotal);
    _cylinder   = new Mesh("cylinder.obj", vertexTotal);
    _sphere     = new Mesh("sph.obj", vertexTotal);
    
    _navMesh    = new GenMesh();
    _navMesh->addTri(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f), glm::vec3(5.0f, 20.0f, 10.0f));
    _navMesh->addTri(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f), glm::vec3(5.0f, -20.0f, 10.0f));
    _navMesh->gen();
    
	LoadTexture("simple.png", _texture);
	LoadTexture("simple1.png", _texture1);
	LoadTexture("simple2.png", _texture2);
	LoadTexture("simple3.png", _texture3);
	LoadTexture("simple4.png", _texture4);
	LoadTexture("simple5.png", _texture5);


	///////////////physics engine initialisations/////////////
	// Specify the dynamic AABB tree broadphase algorithm to be used to work out what objects
	// to test collision for.
	broadphase = new btDbvtBroadphase();

	// The collision configuration allows you to fine tune the algorithms used
	// for the full (not broadphase) collision detection. Here be dragons!
	collisionConfiguration = new btDefaultCollisionConfiguration();

	dispatcher = new btCollisionDispatcher(collisionConfiguration);

	// We also need a "solver". This is what causes the objects to interact
	// properly, taking into account gravity, game logic supplied forces,
	// collisions, and hinge constraints. It does a good job as long as you
	// don't push it to extremes, and is one of the bottlenecks in any high
	// performance simulation. There are parallel versions available for some
	// threading models.
	solver = new btSequentialImpulseConstraintSolver;

	// Now, we can finally instantiate the dynamics world.
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	// Set the gravity. We have chosen the Y axis to be "up".
	dynamicsWorld->setGravity(btVector3(0, -10, 0));
	//////////////////////////////////////////////////////////////////////////
	InputInit();
	//////////////////////////////////////////////////////////////////////////
	//shader copilation
	shaderProgram = new ShaderProgram("shaders/vertexSpec.glsl", "shaders/fragmentSpec.glsl");
	shaderProgramSimple = new ShaderProgram("shaders/VertexUI.glsl", "shaders/FragmentUI.glsl");
	//camera game objects
	GameObject * tgo = new GameObject("camera");
	tgo->attachComponent(new Transform(tgo, "transform", new glm::mat4(1.0f), new glm::mat4(1.0f)));
	Transform * tr = tgo->getComponent<Transform>();
	tr->m_localPosition = glm::vec3(0.0f, 5.0f, -15.0f);
	tr->m_localRotation = glm::vec3(0.0f,180.0f,0.0f);
	tgo->attachComponent(new Camera(tgo, "camera", glm::perspectiveFov<float>(45.0f,winWidth, winHeight, 0.1f, 2000.0f)));
	_mainCam = tgo->getComponent<Camera>();
	gameObjects.push_back(tgo);	
    
    /////////////////////////////////////
	//light game objects/////////////////
    /////////////////////////////////////
	tgo = new GameObject("pointLight");
	tgo->attachComponent(new Transform(tgo, "transform", &_mainCam->m_viewMatrix, &_mainCam->m_projectionMatrix));
	tr = tgo->getComponent<Transform>();
	tr->m_localPosition = glm::vec3(20.0f, 10.0f, 20.0f);
	tgo->attachComponent(new PointLight(tgo,"light",shaderProgram,&lightObjects,true, glm::vec3(0.0f,0.0f,0.0f),40.0f));
	tgo->attachComponent(new Material(tgo, "material", &_texture1));
	tgo->attachComponent(new MeshRenderer(tgo, "meshRenderer", _cube, shaderProgramSimple, MeshRenderer::SOLID));
	lightObjects.push_back(tgo->getComponent<Light>());
	gameObjects.push_back(tgo);

	tgo = new GameObject("pointLight2");
	tgo->attachComponent(new Transform(tgo, "transform", &_mainCam->m_viewMatrix, &_mainCam->m_projectionMatrix));
	tr = tgo->getComponent<Transform>();
	tr->m_localPosition = glm::vec3(-20.0f, 10.0f, 20.0f);
	tgo->attachComponent(new PointLight(tgo, "light", shaderProgram, &lightObjects, true, glm::vec3(0.0f, 0.0f, 0.0f), 40.0f));
	tgo->attachComponent(new Material(tgo, "material", &_texture1));
	tgo->attachComponent(new MeshRenderer(tgo, "meshRenderer", _cube, shaderProgramSimple, MeshRenderer::SOLID));
	lightObjects.push_back(tgo->getComponent<Light>());
	gameObjects.push_back(tgo);
    

	tgo = new GameObject("directionalLight");
	tgo->attachComponent(new Transform(tgo, "transform", &_mainCam->m_viewMatrix, &_mainCam->m_projectionMatrix));
	tr = tgo->getComponent<Transform>();
	tr->m_localPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	tgo->attachComponent(new DirectionalLight(tgo, "light", shaderProgram, &lightObjects, true, glm::vec3(0.0f, 0.0f, 0.0f), 0.4f,glm::vec3(1,1,1)));
	lightObjects.push_back(tgo->getComponent<Light>());
	gameObjects.push_back(tgo);
    
    /////////////////////////////////////////
	//game objects///////////////////////////
    /////////////////////////////////////////
	tgo = new GameObject("cube0");
	cube[0] = tgo;
	tgo->attachComponent(new Transform(tgo, "transform", &_mainCam->m_viewMatrix, &_mainCam->m_projectionMatrix));
	tr = tgo->getComponent<Transform>();
	tr->m_localPosition = glm::vec3(1.0f, 20.0f, 4.0f);
	tr->m_localRotation = glm::vec3(0.0f,0.0f,0.0f);
	tr->m_localScale = glm::vec3(1.0f, 1.0f, 1.0f);

	tgo->attachComponent(new Material(tgo, "material", &_texture3));
	tgo->attachComponent(new MeshRenderer(tgo, "meshRenderer", _cube, shaderProgramSimple, MeshRenderer::WIRE));
	tgo->attachComponent(new PhysicsBt(tgo, "PhysicsEngineComponent", dynamicsWorld, new btBoxShape(btVector3(1.0f,1.0f,1.0f)), 1));
	//carBody->getComponent<Particle>()->applyForce(glm::vec3(0.0f, 5000.0f, 0.0f));
	gameObjects.push_back(tgo);
    
    /////////////////////////////////////////
	tgo = new GameObject("cube1");
	cube[1] = tgo;
	tgo->attachComponent(new Transform(tgo, "transform", &_mainCam->m_viewMatrix, &_mainCam->m_projectionMatrix));
	tr = tgo->getComponent<Transform>();
	tr->m_localPosition = glm::vec3(0.0f, 10.0f, 4.0f);
	tr->m_localScale = glm::vec3(1.0f, 1.0f, 1.0f);

	tgo->attachComponent(new Material(tgo, "material", &_texture));
	tgo->attachComponent(new MeshRenderer(tgo, "meshRenderer", _cube, shaderProgram, MeshRenderer::SOLID));
	tgo->attachComponent(new PhysicsBt(tgo, "PhysicsEngineComponent", dynamicsWorld, new btBoxShape(btVector3(1.0f, 1.0f, 1.0f)), 1));
	//carBody->getComponent<Particle>()->applyForce(glm::vec3(0.0f, 5000.0f, 0.0f));
	gameObjects.push_back(tgo);

    //////////////////////////////////////////
	tgo = new GameObject("cube2");
	cube[2] = tgo;
	tgo->attachComponent(new Transform(tgo, "transform", &_mainCam->m_viewMatrix, &_mainCam->m_projectionMatrix));
	tr = tgo->getComponent<Transform>();
	tr->m_localPosition = glm::vec3(0.0f, -1.0f, 4.0f);
	tr->m_localScale = glm::vec3(30.0f, 0.2f, 30.0f);

	tgo->attachComponent(new Material(tgo, "material", &_texture));
	tgo->attachComponent(new MeshRenderer(tgo, "meshRenderer", _cube, shaderProgram, MeshRenderer::SOLID));
	tgo->attachComponent(new PhysicsBt(tgo, "PhysicsEngineComponent", dynamicsWorld, new btBoxShape(btVector3(30.0f, 0.2f, 30.0f)), 0));
	//carBody->getComponent<Particle>()->applyForce(glm::vec3(0.0f, 5000.0f, 0.0f));
	gameObjects.push_back(tgo);
	
    ///////////////////////////////////////////
    
    
    tgo = new GameObject("nav mesh");
	cube[3] = tgo;
	tgo->attachComponent(new Transform(tgo, "transform", &_mainCam->m_viewMatrix, &_mainCam->m_projectionMatrix));
	tr = tgo->getComponent<Transform>();
	tr->m_localPosition = glm::vec3(5.0f, 10.0f, 4.0f);
	tr->m_localScale = glm::vec3(1.0f, 1.0f, 1.0f);

	tgo->attachComponent(new Material(tgo, "material", &_texture));
	tgo->attachComponent(new MeshRenderer(tgo, "meshRenderer", _navMesh, shaderProgramSimple, MeshRenderer::WIRE));
	tgo->attachComponent(new PhysicsBt(tgo, "PhysicsEngineComponent", dynamicsWorld, new btBoxShape(btVector3(1.0f, 1.0f, 1.0f)), 1));
	//carBody->getComponent<Particle>()->applyForce(glm::vec3(0.0f, 5000.0f, 0.0f));
	gameObjects.push_back(tgo);

	

	

}

Scene::~Scene()
{
    
	for (int i = 0; i < gameObjects.size(); i++)
	{
		for (int k = 0; k < gameObjects[i]->m_components.size(); k++)
		{
			delete gameObjects[i]->m_components[k];
		}
		delete gameObjects[i];
	}
}

void Scene::InputInit()
{
	eventHandler->getEvent(ON_E_DOWN)->addSubscriber(EventSubscriber([&]()
	{
		_mainCam->m_transform->m_localPosition += deltaTs *glm::vec3(0, 1, 0)*CAM_SPEED;
	}
	));

	eventHandler->getEvent(ON_Q_DOWN)->addSubscriber(EventSubscriber([&]()
	{
		_mainCam->m_transform->m_localPosition -= deltaTs * glm::vec3(0, 1, 0)*CAM_SPEED;
	}
	));

	eventHandler->getEvent(ON_W_DOWN)->addSubscriber(EventSubscriber([&]()
	{
		_mainCam->m_transform->m_localPosition += deltaTs * glm::normalize(_mainCam->m_cameraFront)*CAM_SPEED;
	}
	));

	eventHandler->getEvent(ON_A_DOWN)->addSubscriber(EventSubscriber([&]()
	{
		glm::vec3 tempSide = glm::cross(UP, _mainCam->m_cameraFront);
		_mainCam->m_transform->m_localPosition += deltaTs *tempSide*CAM_SPEED;
	}
	));

	eventHandler->getEvent(ON_S_DOWN)->addSubscriber(EventSubscriber([&]()
	{
		_mainCam->m_transform->m_localPosition -= deltaTs * _mainCam->m_cameraFront*CAM_SPEED;
	}
	));

	eventHandler->getEvent(ON_D_DOWN)->addSubscriber(EventSubscriber([&]()
	{
		glm::vec3 tempSide = glm::cross(UP, _mainCam->m_cameraFront);
		_mainCam->m_transform->m_localPosition -= deltaTs *tempSide*CAM_SPEED;
	}
	));

	




}

void Scene::Update(float _deltaTs)
{
	deltaTs = _deltaTs;
		
	SDL_PumpEvents();
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	SDL_GetMouseState(&mX, &mY);
	int dX = winWidth / 2 - mX;
	int dY = winHeight / 2 - mY;
	
	_mainCam->m_transform->m_localRotation.x += 40*(_deltaTs *(dY)*3.14159265358979323846 / 180.0f);
	_mainCam->m_transform->m_localRotation.y += 40*(_deltaTs *(dX)*3.14159265358979323846 / 180.0f);
	//printf("x: %d  y: %d \n", mX, mY);

	SDL_WarpMouseInWindow(window, winWidth / 2, winHeight / 2);
	/////=================================================
	
	float moveSpeed = 10.0f;

// 	if (state[SDL_SCANCODE_W])
// 	{
// 		//printf("W pressed \n");			
// 		_mainCam->m_transform->m_localPosition += _deltaTs *  glm::normalize(_mainCam->m_cameraFront) *moveSpeed;
// 	}
// 
// 	if (state[SDL_SCANCODE_S])
// 	{
// 		_mainCam->m_transform->m_localPosition -= _deltaTs * _mainCam->m_cameraFront *moveSpeed;
// 	}
// 
// 	if (state[SDL_SCANCODE_D])
// 	{
// 		glm::vec3 tempSide = glm::cross(UP, _mainCam->m_cameraFront);
// 		_mainCam->m_transform->m_localPosition -= _deltaTs *tempSide*moveSpeed;
// 	}
// 	if (state[SDL_SCANCODE_A])
// 	{
// 		glm::vec3 tempSide = glm::cross(UP, _mainCam->m_cameraFront);
// 		_mainCam->m_transform->m_localPosition += _deltaTs *tempSide*moveSpeed;
// 	}


	if (state[SDL_SCANCODE_T])
	{
		cube[0]->getComponent<PhysicsBt>()->m_rigidBody->applyTorque(btVector3(40.0f,0.0f,0.0f));
	}
	////////////////////////////////////////////////
	dynamicsWorld->stepSimulation(1 / 60.f, 10);
}

void Scene::Draw()
{
	//glUseProgram(shaderProgramSimple->m_shaderProgramLocation);
	//glUniform1i(_shaderNumLightsLocation, lightObjects.size());

	glBindFramebuffer(GL_FRAMEBUFFER, 0);//<-----------render to the original buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//==============================================================
	//mow down through every object in the scene
	for (int i = 0; i < gameObjects.size();i++)
	{
		
		for (int j = 0; j < gameObjects[i]->m_components.size();j++)
		{
			gameObjects[i]->m_components[j]->update();
		}

	}


	//draw axis
	glUseProgram(shaderProgramSimple->m_shaderProgramLocation);
	glUniformMatrix4fv(shaderProgramSimple->m_shaderRotMatLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
	glUniformMatrix4fv(shaderProgramSimple->m_shaderModelMatLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));

	glUniformMatrix4fv(shaderProgramSimple->m_shaderViewMatLocation, 1, GL_FALSE, glm::value_ptr(_mainCam->m_viewMatrix));
	glUniformMatrix4fv(shaderProgramSimple->m_shaderProjMatLocation, 1, GL_FALSE, glm::value_ptr(_mainCam->m_projectionMatrix));
	
	glBindTexture(GL_TEXTURE_2D, _texture);
	_line.Draw(glm::vec3(0, 0, 0), glm::vec3(2, 0, 0));
	glBindTexture(GL_TEXTURE_2D, _texture3);
	_line.Draw(glm::vec3(0, 0, 0), glm::vec3(0, 2, 0));
	glBindTexture(GL_TEXTURE_2D, _texture4);
	_line.Draw(glm::vec3(0, 0, 0), glm::vec3(0, 0, 2));

	///////////////debugging///////////
	
	//_circle.Draw(cube0->getComponent<SphereBV>()->m_center, cube0->getComponent<SphereBV>()->m_radius);
	//_circle.Draw(carBody->getComponent<SphereBV>()->m_center, carBody->getComponent<SphereBV>()->m_radius);
	//_circle.Draw(plane0->getComponent<SphereBV>()->m_center, plane0->getComponent<SphereBV>()->m_radius);
	glUseProgram(0);
}



void Scene::LoadTexture(std::string filename, GLuint &texLocation)
{

	SDL_Surface *image = IMG_Load(filename.c_str());
	if (!image)
	{
		printf("IMG_Load: %s\n", IMG_GetError());
		// handle error
	}
	/*SDL_Surface *image = SDL_LoadBMP(filename.c_str());

	if (!image)
	{
		std::cerr << "WARNING: could not load BMP image: " << filename << std::endl;
	}*/

	// The SDL_Surface is a data structure
	// image->w  is the width
	// image->h  is the height
	// image->pixels   is the raw pixel data you need to send to OpenGL
	// SDL loads images in BGR order
	// You'll need to send the data to OpenGL like this:

	//the numer used for importing arrays of textures
	glGenTextures(1, &texLocation);
	glBindTexture(GL_TEXTURE_2D, texLocation);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_BGR, GL_UNSIGNED_BYTE, image->pixels);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);*/

	glBindTexture(GL_TEXTURE_2D, 0);
	SDL_FreeSurface(image);

}

void Scene::LoadTextureA(std::string filename, GLuint &texLocation)
{

	SDL_Surface *image = IMG_Load(filename.c_str());
	if (!image)
	{
		printf("IMG_Load: %s\n", IMG_GetError());
		// handle error
	}
	/*SDL_Surface *image = SDL_LoadBMP(filename.c_str());

	if (!image)
	{
	std::cerr << "WARNING: could not load BMP image: " << filename << std::endl;
	}*/

	

	//the numer used for importing arrays of textures
	glGenTextures(1, &texLocation);
	glBindTexture(GL_TEXTURE_2D, texLocation);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_BGR, GL_UNSIGNED_BYTE, image->pixels);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);
	SDL_FreeSurface(image);

}

void Scene::BuildFBO(GLuint &_fbo, GLuint &_texAtt)
{
	glGenFramebuffers(1, &_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, _fbo);

	// The texture we're going to render to
	glGenTextures(1, &_texAtt);
	glBindTexture(GL_TEXTURE_2D, _texAtt);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, 800, 600, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);

	//// The depth buffer
	//glGenRenderbuffers(1, &_renderBuffer);

	//glBindRenderbuffer(GL_RENDERBUFFER, _renderBuffer);

	//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 800, 600);

	//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _renderBuffer);

	// Set "renderedTexture" as our colour attachement #0
	//glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, _renderTexture, 0);

	
	//glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, _texAtt, 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, _texAtt, 0);
	glDrawBuffer(GL_NONE);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		cout << "Frame buffer failed!" << endl;;
	}


}

//print text
void Scene::renderText(GLuint &texLocation,char * message, char * fontFile, SDL_Color color, int fontSize)
{

//	TTF_Font *font = TTF_OpenFont(fontFile, fontSize);
//	if (font == nullptr)
//	{
//		cout << "Failed to open font file." << endl;
//	}

//	SDL_Surface *surf = TTF_RenderUTF8_Blended(font, message, color);//TTF_RenderText_Solid(font, message, color);//IMG_Load("TEMP_CRAP.bmp"); 
	
//	if (surf == nullptr)
//	{
//		cout << "Failed to create render to a surface." << endl;
//	}


	//GLenum texture_format;
	//GLenum colors = surf->format->BytesPerPixel;
	//if (colors == 4)
	//{   // alpha
	//	if (surf->format->Rmask == 0x000000ff)
	//		texture_format = GL_RGBA;
	//	else
	//		texture_format = GL_BGRA;
	//}
	//else
	//{             // no alpha
	//	if (surf->format->Rmask == 0x000000ff)
	//		texture_format = GL_RGB;
	//	else
	//		texture_format = GL_BGR;
	//}



	//SDL_SaveBMP(surf, "TEMP_CRAP.bmp");

	//glGenTextures(1, &texLocation);
	//glBindTexture(GL_TEXTURE_2D, texLocation);
	//
	////std::vector<char> abc(surf->w * surf->h * 4);
	////memcpy(&abc[0], surf->pixels, sizeof(char) * surf->w * surf->h * 4);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,surf->w, surf->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, surf->pixels);

	//glBindTexture(GL_TEXTURE_2D, 0);


	//Clean up the surface and font
	/*SDL_FreeSurface(surf);
	TTF_CloseFont(font);*/
}

