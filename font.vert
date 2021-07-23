#version 330 core

//attributes only work in vert shaders and the .cpp files
attribute vec2 aPosition;
attribute vec2 aTexture;

//varying is a type of data/variable that produces a interpolated value between vert and frag shaders
varying vec2 vTexCoord;

uniform mat4 ModViewProj;

void main(){
	gl_Position = ModViewProj * vec4(aPosition, 0.5f, 1.0f);

	vTexCoord = aTexture;
}