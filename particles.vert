#version 330

layout (location = 0) in vec4 vertex;

out vec2 TexCoords;
out vec4 particleColor;

uniform mat4 proj;
uniform vec2 offset;
uniform vec4 color;

void main(){
	float scale = 1.0f;
	TexCoords = vertex.zw;
	particleColor = color;
	gl_Position = proj * vec4((vertex.xy * scale) + offset, 0.0, 1.0);
}