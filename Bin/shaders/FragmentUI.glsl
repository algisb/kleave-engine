#version 430 core


in vec2 vTexCoordOut;
uniform sampler2D tex1;
out vec4 fragColour;

void main()
{
	//fragColour = vec4(1.0);
	//vec3 texColour = vec3(texture(tex1, vTexCoordOut));
	fragColour = vec4(texture(tex1, vTexCoordOut));
}