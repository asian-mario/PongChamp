#version 330

layout (location = 0) in vec4 vertex;

out vec2 TexCoords;
out vec4 particleColor;

uniform mat4 proj;
uniform vec2 offset;
uniform vec4 color;

uniform vec3 scale;
uniform float xPosC;

void main(){

	TexCoords = vertex.zw;
	particleColor = color;
	gl_Position = proj * vec4((vertex.xy * scale.x) + offset, 0.0, 1.0);
}