#version 330 core

varying vec2 vTexCoord;

uniform sampler2D u_texture;

void main(){
	gl_FragColor = vec4(texture(u_texture, vTexCoord).a);
}