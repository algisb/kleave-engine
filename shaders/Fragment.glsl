#version 430 core

struct LightProperties 
{
	int isEnabled; // true to apply this light in this invocation
	vec3 position; // location of light, if is Local is true,

	int isSpot;
	vec3 coneDirection;
	float spotCosCutoff;
	float spotExponent;

	int isDir;
	vec3 dir;

	vec3 lightColour;
	float strength;
};

struct MaterialProperties
{
	vec3 emissiveColour;
	vec3 diffuseColour;
	vec3 specularColour;
	float shininess;
	float alpha;
	int normalMap;
};

in vec3 vNormalV;
in vec2 vTexCoordOut;
in vec4 shadowCoord;

in vec3 vertexPosition_cameraspace;

//in vec3 LightPosition_cameraspace;
in mat3 TBN;

uniform vec3 ambientColour = { 0.05f, 0.05f, 0.05f };

//lights
uniform int numLights;
uniform LightProperties light[10];

//material
uniform MaterialProperties material;

//texture
uniform sampler2D tex1;
uniform sampler2D norm1;
uniform sampler2DShadow shadowMap1;
uniform samplerCube cubeMap1;

uniform mat4 viewMat;
out vec4 fragColour;
void main()
{
	fragColour = vec4(ambientColour, material.alpha);
	for (int i = 0; i < numLights;i++)
	{
		if (light[i].isEnabled == 1)
		{
			//pointlights
			if (light[i].isSpot == 0 && light[i].isDir == 0)
			{
				vec3 LightPosition_cameraspace = (viewMat * vec4(light[i].position, 1)).xyz;
				vec3 EyeDirection_cameraspace = normalize(vec3(0, 0, 0) - vertexPosition_cameraspace);
				vec3 LightDirection_cameraspace = normalize(LightPosition_cameraspace - vertexPosition_cameraspace);

				vec3 lightDir = normalize(TBN * normalize(LightDirection_cameraspace));
				vec3 camDir = normalize(TBN * normalize(EyeDirection_cameraspace));


				//float vis = texture(shadowMap1, vec3(shadowCoord.xy, (shadowCoord.z - 0.005) / shadowCoord.w));
				float vis = 1.0f;
				if (material.normalMap == 1)
				{
					float att = 1 / pow(length(LightPosition_cameraspace - vertexPosition_cameraspace), 2);

					vec3 normal = normalize(texture(norm1, vTexCoordOut).rgb*2.0 - 1.0);

					float diff = clamp(dot(normal, lightDir), 0, 1);
					vec3 texColour = vec3(texture(tex1, vTexCoordOut));
					vec3 diffuse = diff*texColour;

					float spec = clamp(dot(reflect(-lightDir, normal), camDir), 0, 1);
					spec = pow(spec, material.shininess);
					vec3 specular = spec * material.specularColour;

					fragColour = fragColour + vec4(light[i].lightColour + material.emissiveColour + material.diffuseColour + (diffuse + specular) * att * light[i].strength*vis, material.alpha);
				}

				else if (material.normalMap == 0)
				{
					//======= vertex normal
					vec3 normal = normalize(vNormalV);
					float att = 1 / pow(length(LightPosition_cameraspace - vertexPosition_cameraspace), 2);
					float diff = max(0.0, dot(normal, LightDirection_cameraspace));
					vec3 texColour = vec3(texture(tex1, vTexCoordOut));
					vec3 diffuse = diff*texColour;

					float spec = max(0.0, dot(reflect(LightDirection_cameraspace, normal), EyeDirection_cameraspace));
					spec = pow(spec, material.shininess);
					vec3 specular = spec * material.specularColour;

					fragColour = fragColour + vec4(light[i].lightColour + material.emissiveColour + material.diffuseColour + (diffuse + specular)* att * light[i].strength*vis, material.alpha);
				}

			}

			//spotlights
			else if (light[i].isSpot == 1)
			{
				

				vec3 LightPosition_cameraspace = (viewMat * vec4(light[i].position, 1)).xyz;
				vec3 EyeDirection_cameraspace = normalize(vec3(0, 0, 0) - vertexPosition_cameraspace);
				vec3 LightDirection_cameraspace = normalize(LightPosition_cameraspace - vertexPosition_cameraspace);

				vec3 lightDir = normalize(TBN * normalize(LightDirection_cameraspace));
				vec3 camDir = normalize(TBN * normalize(EyeDirection_cameraspace));
				float vis = 1.0f;
				if (material.normalMap == 1)
				{
					float att = 1 / pow(length(LightPosition_cameraspace - vertexPosition_cameraspace), 2);
					float spotCos = dot(LightDirection_cameraspace, -normalize(light[i].coneDirection));
					if (spotCos < light[i].spotCosCutoff)
					{
						att = 0.0f;
					}
					else
					{
						att *= pow(spotCos, light[i].spotExponent);
					}

					vec3 normal = normalize(texture(norm1, vTexCoordOut).rgb*2.0 - 1.0);

					float diff = clamp(dot(normal, lightDir), 0, 1);
					vec3 texColour = vec3(texture(tex1, vTexCoordOut));
					vec3 diffuse = diff*texColour;

					float spec = clamp(dot(reflect(-lightDir, normal), camDir), 0, 1);
					spec = pow(spec, material.shininess);
					vec3 specular = spec * material.specularColour;


					fragColour = fragColour + vec4(light[i].lightColour + material.emissiveColour + material.diffuseColour + (diffuse + specular) * att * light[i].strength*vis, material.alpha);
				}

				else if (material.normalMap == 0)
				{
					//======= vertex normal
					float att = 1 / pow(length(LightPosition_cameraspace - vertexPosition_cameraspace), 2);
					float spotCos = dot(LightDirection_cameraspace, -normalize(light[i].coneDirection));
					if (spotCos < light[i].spotCosCutoff)
					{
						att = 0.0f;
					}
					else
					{
						att *= pow(spotCos, light[i].spotExponent);
					}

					vec3 normal = normalize(vNormalV);

					float diff = max(0.0, dot(normal, LightDirection_cameraspace));
					vec3 texColour = vec3(texture(tex1, vTexCoordOut));
					vec3 diffuse = diff*texColour;

					float spec = max(0.0, dot(reflect(LightDirection_cameraspace, normal), EyeDirection_cameraspace));
					spec = pow(spec, material.shininess);
					vec3 specular = spec * material.specularColour;


					fragColour = fragColour + vec4(light[i].lightColour + material.emissiveColour + material.diffuseColour + (diffuse + specular) * att * light[i].strength*vis, material.alpha);
				}

			}
			//directional lights
			else if (light[i].isDir == 1)
			{
				//float att = 1 / pow(length(light[i].position - eyeSpaceVertPosV), 2);

				vec3 LightPosition_cameraspace = (viewMat * vec4(light[i].position, 1)).xyz;
				vec3 EyeDirection_cameraspace = normalize(vec3(0, 0, 0) - vertexPosition_cameraspace);
				vec3 LightDirection_cameraspace = normalize(light[i].dir);

				vec3 lightDir = normalize(TBN * normalize(LightDirection_cameraspace));
				vec3 camDir = normalize(TBN * normalize(EyeDirection_cameraspace));
				float vis = texture(shadowMap1, vec3(shadowCoord.xy, (shadowCoord.z-0.005) / shadowCoord.w));

				if (material.normalMap == 1)
				{
					vec3 normal = normalize(texture(norm1, vTexCoordOut).rgb*2.0 - 1.0);

					float diff = clamp(dot(normal, lightDir), 0, 1);
					vec3 texColour = vec3(texture(tex1, vTexCoordOut));
					vec3 diffuse = diff*texColour;

					float spec = clamp(dot(reflect(-lightDir, normal), camDir), 0, 1);
					spec = pow(spec, material.shininess);
					vec3 specular = spec * material.specularColour;


					fragColour = fragColour + vec4(light[i].lightColour + material.emissiveColour + material.diffuseColour + (diffuse + specular) * light[i].strength*vis, material.alpha);
				}
				else if (material.normalMap == 0)
				{
					//======= vertex normal
					vec3 normal = normalize(vNormalV);

					float diff = max(0.0, dot(normal, LightDirection_cameraspace));
					vec3 texColour = vec3(texture(tex1, vTexCoordOut));
					vec3 diffuse = diff*texColour;

					float spec = max(0.0, dot(reflect(LightDirection_cameraspace, normal), EyeDirection_cameraspace));
					spec = pow(spec, material.shininess);
					vec3 specular = spec * material.specularColour;


					fragColour = fragColour + vec4(light[i].lightColour + material.emissiveColour + material.diffuseColour + (diffuse + specular) * light[i].strength*vis, material.alpha);
				}
				

				
			}



		}
	}


}