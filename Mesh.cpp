
#include "Mesh.h"

Mesh::Mesh(char * _fileName, unsigned int &_totalVertex)
{
	Obj2 obj2(_fileName);
	obj2.loadAll();
	obj2.convertVertexRTE();
	obj2.convertVertexNormalRTE();
	obj2.convertVertexTextureRTE();
	obj2.convertoObjToGlm();
	obj2.computeTangentBasis();
	if (obj2.v)
	{
		m_vao = 0;

		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

		m_numVertices = obj2.VRTE.size() / 3;

		_totalVertex = _totalVertex + m_numVertices;
		GLuint buffer = 0;
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_numVertices * 3, &obj2.VRTE[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
	}


	
	if (obj2.vn)
	{
		GLuint normalBuffer = 0;
		glGenBuffers(1, &normalBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_numVertices * 3, &obj2.VNRTE[0], GL_STATIC_DRAW);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);
	}

	if (obj2.vt)
	{
		GLuint texcoordBuffer = 0;
		glGenBuffers(1, &texcoordBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, texcoordBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_numVertices * 2, &obj2.VTRTE[0], GL_STATIC_DRAW);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(2);
	}
	

	 GLuint tangentbuffer;
     glGenBuffers(1, &tangentbuffer);
     glBindBuffer(GL_ARRAY_BUFFER, tangentbuffer);
	 glBufferData(GL_ARRAY_BUFFER, obj2.tangents.size()*sizeof(glm::vec3), &obj2.tangents[0], GL_STATIC_DRAW);
	 glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);
	 glEnableVertexAttribArray(3);
	 
     GLuint bitangentbuffer;
     glGenBuffers(1, &bitangentbuffer);
     glBindBuffer(GL_ARRAY_BUFFER, bitangentbuffer);
	 glBufferData(GL_ARRAY_BUFFER, obj2.bitangents.size()*sizeof(glm::vec3), &obj2.bitangents[0], GL_STATIC_DRAW);
	 glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, 0);
	 glEnableVertexAttribArray(4);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Technically we can do this, because the enabled / disabled state is stored in the VAO
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
}

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
	glDeleteVertexArrays( 1, &m_vao );
}

GenMesh::GenMesh()
{
}

GenMesh::~GenMesh()
{
}

void GenMesh::addTri(glm::vec3 _p0, glm::vec3 _p1, glm::vec3 _p2)
{
    m_verticies.push_back(_p0);
    m_verticies.push_back(_p1);
    m_verticies.push_back(_p2);
}

void GenMesh::gen()
{
        m_vao = 0;

		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);
        
        m_numVertices = m_verticies.size();
		GLuint buffer = 0;
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_verticies.size(), &m_verticies[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
}


void MeshLine::Draw(glm::vec3 _p1, glm::vec3 _p2)
{
	glm::vec3 vertexData[2] = { _p1, _p2 };
	GLuint _VAO = 0;

	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);

	int _numVertices = 2;

	//totalVertex = totalVertex + _numVertices;
	GLuint buffer = 0;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _numVertices * 3, vertexData, GL_DYNAMIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);


	// Tell OpenGL to draw it
	// Must specify the type of geometry to draw and the number of vertices
	glDrawArrays(GL_LINE_STRIP, 0, _numVertices);
	// Unbind VAO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &buffer);
	glDeleteVertexArrays(1, &_VAO);

}

void MeshPoint::Draw(glm::vec3 _p)
{
	glm::vec3 vertexData[1] = { _p };
	GLuint _VAO = 0;

	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);

	int _numVertices = 1;

	//totalVertex = totalVertex + _numVertices;
	GLuint buffer = 0;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _numVertices * 3, vertexData, GL_DYNAMIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);


	// Tell OpenGL to draw it
	// Must specify the type of geometry to draw and the number of vertices
	glDrawArrays(GL_POINTS, 0, _numVertices);
	// Unbind VAO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &buffer);
	glDeleteVertexArrays(1, &_VAO);
}

void MeshCircle::Draw(glm::vec3 _center, float _radius)
{
	glm::vec3 tempFirst = glm::vec3(0, _radius,0);
	for (int i = 0; i < 361; i++)
	{
		float tempAngle = i*3.14159265358979323846 / 180.0f;
		
		glm::vec3 tempPoint = glm::mat3(glm::rotate(glm::mat4(1.0f), tempAngle, glm::vec3(0, 0, 1)))* tempFirst;
		tempPoint += _center;
		m_frag.Draw(tempPoint);
	}
}
