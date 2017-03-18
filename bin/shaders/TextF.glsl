#version 430 core

// Interpolated values from the vertex shaders
in vec2 UV;

// Ouput data
out vec4 fragColour;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;

void main(){

	fragColour = texture( myTextureSampler, UV );
	
	
}