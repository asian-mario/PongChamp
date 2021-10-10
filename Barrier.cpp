#include "Barrier.h"

Barrier::Barrier(glm::vec3 position, glm::vec3 scale, std::string name) {
	this->position = glm::vec3(position);
	this->scale = glm::vec3(scale);
	this->name = name;
	this->boundingBox = createBoundingBox();
}

