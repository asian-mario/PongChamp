#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"

class Mesh;
class Game;

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

	
	virtual glm::mat4 getModelMatrix();
	virtual glm::vec3 findWorldPos();
	virtual void draw(Game* game);
	virtual void update(Game* game) {}
};

