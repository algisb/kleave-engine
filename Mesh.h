
#ifndef __MESH_H__
#define __MESH_H__

// This is the main SDL include file
#include "SDL.h"
#include "SDL_image.h"
#include "glew.h"
#include "Obj2.h"
#include "glm.hpp" // This is the main GLM header
#include "gtc/matrix_transform.hpp" 

class Mesh
{
public:
	Mesh(char * fileName, unsigned int &totalVertex);
	Mesh();
	~Mesh();

	virtual void Draw();

	std::vector<glm::vec3> vertices;

	std::vector<glm::vec2> uvs;

	std::vector<glm::vec3> normals;


	std::vector<glm::vec3> tangents;

	std::vector<glm::vec3> bitangents;

	
protected:
	GLuint _VAO;
	unsigned int _numVertices;


	

};

class MeshLine
{
public:
	MeshLine()
	{}
	~MeshLine()
	{}
	void Draw(glm::vec3 _p1, glm::vec3 _p2);

};

class MeshPoint
{
public:
	MeshPoint()
	{}
	~MeshPoint()
	{}

	void Draw(glm::vec3 _p);

};
class MeshCircle
{
public:
	MeshPoint m_frag;
	MeshCircle()
	{}
	~MeshCircle()
	{}
	void Draw(glm::vec3 _center, float _radius);
};
#endif
