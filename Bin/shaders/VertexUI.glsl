#version 430 core

layout(location = 0) in vec4 vPosition;
layout(location = 2) in vec2 vTexCoordIn;

layout(location = 1) in vec3 vNormalIn;
layout(location = 3) in vec3 vTangentIn;
layout(location = 4) in vec3 vBitangentIn;

uniform mat4 rotMat;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;


out vec2 vTexCoordOut;
void main()
{
	vTexCoordOut = vTexCoordIn;
	vec4 rotPos = rotMat * vPosition;
	gl_Position = projMat * viewMat * modelMat * rotPos;
}