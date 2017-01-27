#include "ShaderManager.h"


ShaderProgram::ShaderProgram(char * _vertexShaderDir, char * _fragmentShaderDir)
{
	BuildShader(m_shaderProgramLocation, _vertexShaderDir, _fragmentShaderDir);
	m_shaderRotMatLocation = glGetUniformLocation(m_shaderProgramLocation, "rotMat");
	m_shaderModelMatLocation = glGetUniformLocation(m_shaderProgramLocation, "modelMat");
	m_shaderViewMatLocation = glGetUniformLocation(m_shaderProgramLocation, "viewMat");
	m_shaderProjMatLocation = glGetUniformLocation(m_shaderProgramLocation, "projMat");
	m_shaderText1SamplerLocation = glGetUniformLocation(m_shaderProgramLocation, "tex1");

	//m_shaderIsEnabledLocation = glGetUniformLocation(m_shaderProgram, "isEnabled");
	//m_shaderPositionLocation = glGetUniformLocation(m_shaderProgram, "position");
	//m_shaderLightColourLocation = glGetUniformLocation(m_shaderProgram, "lightColour");
	//m_shaderStrenghtLocation = glGetUniformLocation(m_shaderProgram, "strength");

	
	
	
	
}
ShaderProgram::~ShaderProgram()
{

}

string ShaderProgram::LoadShader(const char *filePath)
{
	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);

	if (!fileStream.is_open())
	{
		std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
		return "";
	}

	std::string line;
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

bool ShaderProgram::CheckShaderCompiled(GLint shader)
{
	GLint compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		GLsizei len;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

		// OpenGL will store an error message as a string that we can retrieve and print
		GLchar* log = new GLchar[len + 1];
		glGetShaderInfoLog(shader, len, &len, log);
		std::cerr << "ERROR: Shader compilation failed: " << log << std::endl;
		delete[] log;

		return false;
	}
	return true;
}

void ShaderProgram::BuildShader(GLuint &_shaderProgramX, char * vertexShaderDir, char * fragmentShaderDir)
{
	// The vertex position in eye-space is the incoming vertex position (object space) multiplied by the modelview matrix
	// The light position in eye-space is the incoming light position (world space) multiplied by the view matrix
	//=======================shader================================
	std::string vs = LoadShader(vertexShaderDir);
	const GLchar *vShaderText = vs.c_str();

	// This is the fragment shader
	std::string fs = LoadShader(fragmentShaderDir);
	const GLchar *fShaderText = fs.c_str();

	// The 'program' stores the shaders
	_shaderProgramX = glCreateProgram();

	// Create the vertex shader
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	// Give GL the source for it
	glShaderSource(vShader, 1, &vShaderText, NULL);
	// Compile the shader
	glCompileShader(vShader);
	// Check it compiled and give useful output if it didn't work!
	if (!CheckShaderCompiled(vShader))
	{
		std::cerr << "ERROR: failed to compile vertex shader" << std::endl;
		return;
	}
	// This links the shader to the program
	glAttachShader(_shaderProgramX, vShader);



	// Same for the fragment shader
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fShaderText, NULL);
	glCompileShader(fShader);
	if (!CheckShaderCompiled(fShader))
	{
		std::cerr << "ERROR: failed to compile fragment shader" << std::endl;
		return;
	}
	glAttachShader(_shaderProgramX, fShader);

	// This makes sure the vertex and fragment shaders connect together
	glLinkProgram(_shaderProgramX);
	// Check this worked
	GLint linked;
	glGetProgramiv(_shaderProgramX, GL_LINK_STATUS, &linked);
	if (!linked)
	{
		GLsizei len;
		glGetProgramiv(_shaderProgramX, GL_INFO_LOG_LENGTH, &len);

		GLchar* log = new GLchar[len + 1];
		glGetProgramInfoLog(_shaderProgramX, len, &len, log);
		std::cerr << "ERROR: Shader linking failed: " << log << std::endl;
		delete[] log;

		return;
	}




}
