#version 430 core
struct LightProperties
{
	int enabled;
	vec3 position;
	vec3 lightColour;
	float strength;

	int lightType;
	vec3 lightDirection;
};

//lights
uniform int numLights;
uniform LightProperties light[10];
uniform vec3 ambientColour = { 0.05f, 0.05f, 0.05f };

//working stuff
in vec3 vNormalV;
in vec2 vTexCoordOut;
in vec3 vertexPosition_cameraspace;
uniform sampler2D tex1;

out vec4 fragColour;

void main()
{
	fragColour = vec4(ambientColour, 1.0f);
	for (int i = 0; i < numLights;i++)
	{
		vec3 LightPosition_cameraspace = (vec4(light[i].position, 1)).xyz;
		vec3 EyeDirection_cameraspace = normalize(vec3(0, 0, 0) - vertexPosition_cameraspace);
		vec3 normal = normalize(vNormalV);

		if (light[i].lightType == 0)//POINT LIGHT
		{
			vec3 LightDirection_cameraspace = normalize(LightPosition_cameraspace - vertexPosition_cameraspace);

			float att = 1 / pow(length(LightPosition_cameraspace - vertexPosition_cameraspace), 2);
			float diff = max(0.0, dot(normal, LightDirection_cameraspace));
			vec3 texColour = vec3(texture(tex1, vTexCoordOut));
			vec3 diffuse = diff*texColour;

			float spec = max(0.0, dot(reflect(LightDirection_cameraspace, normal), EyeDirection_cameraspace));
			spec = pow(spec, 50.0f);
			vec3 specular = spec * vec3(1.0f, 1.0f, 1.0f);

			fragColour = fragColour + vec4(light[i].lightColour + (diffuse + specular)* att * light[i].strength, 1.0f);

		}

		if (light[i].lightType == 1)//DIRECTIONAL LIGHT
		{
			vec3 LightDirection_cameraspace = light[i].lightDirection;

			float diff = max(0.0, dot(normal, LightDirection_cameraspace));
			vec3 texColour = vec3(texture(tex1, vTexCoordOut));
			vec3 diffuse = diff*texColour;

			float spec = max(0.0, dot(reflect(LightDirection_cameraspace, normal), EyeDirection_cameraspace));
			spec = pow(spec, 50.0f);
			vec3 specular = spec * vec3(1.0f, 1.0f, 1.0f);

			fragColour = fragColour + vec4(light[i].lightColour + (diffuse + specular)* light[i].strength, 1.0f);
		}
		
	}

	///===================
	/*vec3 normal = normalize(vNormalV);
	float diff = max(0.0, dot(normal, LightDirection_cameraspace));
	vec3 texColour = vec3(texture(tex1, vTexCoordOut));
	vec3 diffuse = diff*texColour;


	fragColour = fragColour + vec4(diffuse +  light[0].strength, 1.0f);*/
	//========================

	//fragColour = vec4(1.0);
	//vec3 texColour = vec3(texture(tex1, vTexCoordOut));

	//fragColour = vec4(texture(tex1, vTexCoordOut)); //<<-------- original frag out
}