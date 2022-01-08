#pragma once
#pragma warning (disable : 4996)

#include <cstdio>
#include <glad/glad.h>
#include "VAO.h"
#include <stb/stb_truetype.h>
#include<glm/glm.hpp>
#include <GLFW/glfw3.h>

class Game;
class GLFWwindow;

struct fontVertex {
	glm::vec2 position;
	glm::vec2 texCoords;
};

struct Font {
public:
	VAO fontVAO;
	VBO fontVBO;
	~Font() {
		if (fvBufferData) {
			delete[]fvBufferData;
		}
	}
	void initFont(const char* filename) {
		uint8_t *ttfBuffer = new uint8_t[1<<20];
		uint8_t *tmpBitmap = new uint8_t[512 * 512]; //res of the bitmap

		fread(ttfBuffer, 1, 1 << 20, fopen(filename, "rb")); //rb makes and writes into a binary file
		stbtt_BakeFontBitmap(ttfBuffer, 0, 128.0f, tmpBitmap, 512, 512, 32, 96, cdata); //there are 96 printable ascii characters, cool stuff

		glGenTextures(1, &fontTexture);
		glBindTexture(GL_TEXTURE_2D, fontTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 512, 512, 0, GL_RED, GL_UNSIGNED_BYTE, tmpBitmap);
		glBindTexture(GL_TEXTURE_2D, fontTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0); //unbind texture

		fvBufferCapacity = 20;
		fvBufferData = new fontVertex[fvBufferCapacity * 6];

		
		fontVAO.Bind();
		fontVBO.Bind();
		glBufferData(GL_ARRAY_BUFFER, sizeof(fontVertex) * 6 * fvBufferCapacity, 0, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(fontVertex), 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(fontVertex), (const void*)offsetof(fontVertex, texCoords));
		fontVAO.Unbind();

	}

	void drawString(float x, float y, const char* text, Shader* fontShader) {
		fontVAO.Bind();
		fontVBO.Bind();

		uint32_t len = strlen(text);
		if (fvBufferCapacity < len) {
			fvBufferCapacity = len;
			glBufferData(GL_ARRAY_BUFFER, sizeof(fontVertex) * 6 * fvBufferCapacity, 0, GL_DYNAMIC_DRAW);
			delete[]fvBufferData;
			fvBufferData = new fontVertex[fvBufferCapacity * 6];
		}

		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, fontTexture);
		glUniform1i(glGetUniformLocation(fontShader->ID, "u_texture"), 0);

		fontVertex* vData = fvBufferData;
		uint32_t numVertices = 0;
		while (*text) { 
			if (*text >= 32 && *text < 128) {
				stbtt_aligned_quad q;
				stbtt_GetBakedQuad(cdata, 512, 512, *text - 32, &x, &y, &q, 1);

				vData[0].position = glm::vec2(q.x0, q.y0); vData[0].texCoords = glm::vec2(q.s0, q.t0); 
				vData[1].position = glm::vec2(q.x1, q.y0); vData[1].texCoords = glm::vec2(q.s1, q.t0);
				vData[2].position = glm::vec2(q.x1, q.y1); vData[2].texCoords = glm::vec2(q.s1, q.t1);
				vData[3].position = glm::vec2(q.x0, q.y1); vData[3].texCoords = glm::vec2(q.s0, q.t1);
				vData[4].position = glm::vec2(q.x0, q.y0); vData[4].texCoords = glm::vec2(q.s0, q.t0);
				vData[5].position = glm::vec2(q.x1, q.y1); vData[5].texCoords = glm::vec2(q.s1, q.t1);

				vData += 6;
				numVertices += 6;
			}
			++text;
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(fontVertex) * numVertices, fvBufferData);
		glDrawArrays(GL_TRIANGLES, 0, numVertices);
	}


private:
	stbtt_bakedchar cdata[999];
	GLuint fontTexture;
	fontVertex* fvBufferData;
	uint32_t fvBufferCapacity;
};


