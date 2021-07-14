#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glm/glm.hpp>
#include<glad/glad.h>
#include<vector>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texUV;
};
class VBO {
	public:
		//ID reference for VBO
		GLuint ID;
		//makes the VBO
		VBO(std::vector<Vertex>& vertices);

		void Bind();
		void Unbind();
		void Delete();
};
#endif