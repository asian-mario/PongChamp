#pragma once

#include<glm/glm.hpp>
#include "Mesh.h"
#include "game.h"

class GameObject {
public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::vec3 velocity;
	glm::vec3 worldPos;

	Mesh mesh;

	GameObject() = default;

	virtual void update(Game* g);
	virtual glm::mat4 getModelMatrix() {
		glm::mat4 Loc = roml::translate(glm::mat4(1.0f), position);
		glm::mat4 Rot = roml::rotate(glm::mat4(1.0f), rotation.x, 'X') * roml::rotate(glm::mat4(1.0f), rotation.y, 'Y') *roml::rotate(glm::mat4(1.0f), rotation.z, 'Z');
		glm::mat4 Soc = roml::scale(glm::mat4(1.0f), scale);

		return Loc * Rot * Soc;
	}


	virtual glm::vec3 worldPos(glm::mat4 mat, glm::vec3 pos) {
		return mat * glm::vec4(pos, 1.0f);
	}
};
