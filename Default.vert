#version 330 core

//Position/Co-ords
layout (location = 0) in vec3 aPos; 
//Normals
layout (location = 1) in vec3 aNormal;
//Colors
layout (location = 2) in vec3 aColor; 
//Textures
layout (location = 3) in vec2 aTex;


out vec3 crntPos;
out vec3 Normal;
//outputs color for the frag shader
out vec3 color;
//export texture coord
out vec2 texCoord;




//controls scale of verts
uniform float scale;
uniform float time;

uniform mat4 camMatrix;
uniform mat4 model;
void main()
{
	//calculates direction of light
	crntPos = vec3(model * vec4(aPos, 1.0f));

	//assigns colors from the vertex data to "color"
	Normal = aNormal;
	color = aColor;
	texCoord = aTex;



	gl_Position = camMatrix * vec4(crntPos, 1.0);
	/*gl_Position = vec4(newPos.x, aPos.y , newPos.y ,1.0);*/
}

