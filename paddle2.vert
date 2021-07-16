#version 330 core

//Position/Co-ords
layout (location = 0) in vec3 aPos2; 
//Normals
layout (location = 1) in vec3 aNormal2;
//Colors
layout (location = 2) in vec3 aColor2; 
//Textures
layout (location = 3) in vec2 aTex2;


out vec3 crntPos2;
out vec3 Normal2;
//outputs color for the frag shader
out vec3 color2;
//export texture coord
out vec2 texCoord2;




//controls scale of verts
uniform float scale;
uniform float time;

uniform mat4 camMatrix;
uniform mat4 model2;
void main()
{
	//calculates direction of light
	crntPos2 = vec3(model2 * vec4(aPos2, 1.0f));

	//assigns colors from the vertex data to "color"
	Normal2 = aNormal2;
	color2 = aColor2;
	texCoord2 = aTex2;



	gl_Position = camMatrix * vec4(crntPos2, 1.0);
	/*gl_Position = vec4(newPos.x, aPos.y , newPos.y ,1.0);*/
}

