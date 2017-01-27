#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "glew.h"
using namespace std;

// default shader
// can be inherited to edit
class ShaderProgram
{
public:
	GLuint m_shaderProgramLocation;

	//matrix locations
	int m_shaderRotMatLocation;
	int m_shaderModelMatLocation;
	int m_shaderViewMatLocation;
	int m_shaderProjMatLocation;
	//texture sample locations
	int m_shaderText1SamplerLocation;



	ShaderProgram(char * _vertexShaderDir, char * _fragmentShaderDir);
	~ShaderProgram();
private:
	string LoadShader(const char *filePath);
	bool CheckShaderCompiled(GLint shader);
	void BuildShader(GLuint &_shaderProgramX, char * vertexShaderDir, char * fragmentShaderDir);

};

