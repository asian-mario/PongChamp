#version 330 core

//outputs a vec4
out vec4 FragColor;

uniform vec4 lightColor;

void main(){
	FragColor = lightColor;
}