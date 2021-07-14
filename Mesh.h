#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include<string>

#include"VAO.h"
#include"EBO.h"
#include"Camera.h"
#include"Texture.h"



//CPP vectors because its best not to specify the length
class Mesh {
	public:	
		std::vector <Vertex> vertices;
		std::vector <GLuint> indices;
		std::vector <Texture> textures;

		//Store VAO
		VAO VAO;

		//Initializes Mesh
		Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures);
		
		//Draws mesh
		void Draw(Shader& shader, Camera& camera);
};
#endif 