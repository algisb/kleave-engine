#version 430 core

out float fragColour;

void main()
{
	//fragColour = vec4(1.0);
	fragColour = gl_FragCoord.z;
}