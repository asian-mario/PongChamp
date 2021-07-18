#pragma once

class GameObject {
public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::vec3 velocity;

	GameObject(glm::vec3 pos, glm::vec3 rot; glm::vec3 scale);

	void update();
	glm::mat4 modelMat();
};
