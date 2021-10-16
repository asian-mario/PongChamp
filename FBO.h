#pragma once

#include<glad/glad.h>
#include<vector>

#include"game.h"

class FBO {
public:
	GLuint framebufferTexture;
	GLuint ID; 
	GLuint pingpongFBO[2];
	GLuint pingpongBuffer[2];

	bool horizontal = true, first_iteration = true;
	int amount = 8;

	FBO(Game* g);


	void drawRectangleScreen();
	//Ping Pong Framebuffers (pass data back and forth)
	void PingPongBuffers(Game* g);
	void ActivateBloom(Game* g);

	void Bind();
	void Unbind();
	void Delete();
};
