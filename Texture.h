#pragma once

#include<glad/glad.h>
#include<stb/stb_image.h>

#include"shaderclass.h"

class Game;
using namespace std;


class Texture {
	public:
		GLuint ID;
		const char* type;
		GLuint unit;
		// Create Second Framebuffer Texture
		unsigned int bloomTexture;

		Texture(const char* image, const char* texType, GLuint slot, GLenum format, GLenum pixelType);

		void texUnit(Shader& shader, const char* uniform, GLuint unit);
		void Bind();
		void Unbind();
		void Delete();
};


