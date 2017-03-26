
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
	Mesh(char * _fileName, unsigned int &_totalVertex);
    Mesh();
	~Mesh();

	std::vector<glm::vec3> m_verticies;

	std::vector<glm::vec2> m_uvs;

	std::vector<glm::vec3> m_normals;


	std::vector<glm::vec3> m_tangents;

	std::vector<glm::vec3> m_bitangents;

    
	GLuint m_vao;
	unsigned int m_numVertices;


	

};



class GenMesh : public Mesh
{
public:
    GenMesh();
    ~GenMesh();
    void addTri(glm::vec3 _p0, glm::vec3 _p1, glm::vec3 _p2);
    void gen();

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
