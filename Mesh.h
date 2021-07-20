#pragma once


#include<string>

#include "VAO.h"
#include "EBO.h"
#include "shaderclass.h"
#include "Texture.h"

class Camera;

//CPP vectors because its best not to specify the length
class Mesh {
	public:	
		std::vector <Vertex> vertices;
		std::vector <GLuint> indices;
		std::vector <Texture> textures;

		//Store VAO
		VAO VAO;

		//Initializes Mesh
		Mesh() = default;
		Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures);
		
		//Draws mesh
		void Draw(Shader& shader, Camera& camera);
};

