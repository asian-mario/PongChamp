#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ROML.h"

#include "game.h"
#include "Camera.h"
#include "shaderclass.h"
#include "Mesh.h"

class Mesh;

//These are all common throughout most objects

class GameObject {
public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::vec3 velocity;
	glm::vec3 worldPos;
	glm::vec4 color;


	Mesh mesh;

	GameObject() = default;

	virtual void update(Game* g);
	virtual glm::mat4 getModelMatrix();


	virtual glm::vec3 findWorldPos(glm::mat4 mat, glm::vec3 pos);

	virtual void draw(Game* game);
};

