#pragma once

#include<glad/glad.h>
#include<vector>

#include"game.h"

class FBO {
public:
	unsigned int framebufferTexture;
	GLuint ID; 
	FBO(Game* g);

	void drawRectangleScreen();

	void Bind();
	void Unbind();
	void Delete();
};
