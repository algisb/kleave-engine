#version 430 core

layout(location = 0) in vec4 vPosition;
layout(location = 2) in vec2 vTexCoordIn;

layout(location = 1) in vec3 vNormalIn;
layout(location = 3) in vec3 vTangentIn;
layout(location = 4) in vec3 vBitangentIn;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;
//shadow mapping
uniform mat4 depthMVP;


mat4 biasMatrix=
{
	vec4(0.5, 0.0, 0.0, 0.0),

	vec4(0.0, 0.5, 0.0, 0.0),

	vec4(0.0, 0.0, 0.5, 0.0),

	vec4(0.5, 0.5, 0.5, 1.0)
};
//uniform vec4 worldSpaceLightPos = {1,0.0,1,1};
out vec3 vNormalV;
out vec2 vTexCoordOut;	
out vec4 shadowCoord;
//out vec3 lightDir;
//out vec3 camDir;
out vec3 vertexPosition_cameraspace;
//out vec3 LightPosition_cameraspace;
out mat3 TBN;

void main()
{
	
	//UVs
	vTexCoordOut = vTexCoordIn;
	//vertex manipulation
	gl_Position = projMat * viewMat * modelMat * vPosition;
	shadowCoord = biasMatrix * depthMVP * vPosition;

	vertexPosition_cameraspace = (viewMat * modelMat * vPosition).xyz;

	// model to camera = ModelView
	vec3 vertexTangent_cameraspace = normalize(mat3(viewMat * modelMat) * normalize(vTangentIn));
	vec3 vertexBitangent_cameraspace = normalize(mat3(viewMat * modelMat) * normalize(vBitangentIn));
	vec3 vertexNormal_cameraspace = normalize(mat3(viewMat * modelMat) * normalize(vNormalIn));

	TBN = transpose(mat3(
		vertexTangent_cameraspace,
		vertexBitangent_cameraspace,
		vertexNormal_cameraspace
		));// You can use dot products instead of building this matrix and transposing it. See References for details.


	vNormalV = mat3(viewMat * modelMat) * vNormalIn;
	
}