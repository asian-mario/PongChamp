#version 330 core

//outputs color in RGBA
out vec4 FragColor;


in vec3 crntPos;
in vec3 Normal;
//inputs color from vert shader
in vec3 color;
in vec2 texCoord;

uniform sampler2D diffuse0;

//gets specular map (or specular0 in every context)
uniform sampler2D specular0;

uniform vec4 lightColor;
//Specular depends on camPos
uniform vec3 camPos;
uniform vec3 lightPos;

vec4 pointLight(){

	vec3 lightVec = lightPos - crntPos;
	float dist = length(lightVec);
	float a = 3.0;
	float b = 0.7;
	float intensity = 1.0f / (a * dist * dist + b * dist + 1.0f);


	//''''ambient'''' lighting
	float ambient = 0.05f;


	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);

	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16); //(last one controls how defined the specular light is)
	float specular = specAmount * specularLight;

	return (texture(diffuse0, texCoord) * (diffuse * intensity + ambient ) + texture(specular0, texCoord).r * specular * intensity) * lightColor;
}

vec4 directLight(){
	//''''ambient'''' lighting
	float ambient = 0.05f;


	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);

	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16); //(last one controls how defined the specular light is)
	float specular = specAmount * specularLight;

	return (texture(diffuse0, texCoord) * (diffuse + ambient ) + texture(specular0, texCoord).r * specular) * lightColor;
}

vec4 spotlight(){

	float outerCone = 0.90f;
	float innerCone = 0.95f;
	//''''ambient'''' lighting
	float ambient = 0.05f;


	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - crntPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);

	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 32); //(last one controls how defined the specular light is)
	float specular = specAmount * specularLight;

	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
	float intensity = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	return (texture(diffuse0, texCoord) * (diffuse * intensity + ambient ) + texture(specular0, texCoord).r * specular * intensity) * lightColor;
}

void main(){


	//outputs final color
   FragColor = pointLight();
}