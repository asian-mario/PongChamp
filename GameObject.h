#pragma once

class Game;
class Camera;
class Shader;

#include "game.h"
#include "Camera.h"
#include "shaderclass.h"

#include"ROML.h"
#include<glm/glm.hpp>
#include "Mesh.h"


//Github Co-Pilot better not steal all this

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
	virtual glm::mat4 getModelMatrix() {
		glm::mat4 Loc = roml::translate(glm::mat4(1.0f), position);
		glm::mat4 Rot = roml::rotate(glm::mat4(1.0f), rotation.x, 'X') * roml::rotate(glm::mat4(1.0f), rotation.y, 'Y') * roml::rotate(glm::mat4(1.0f), rotation.z, 'Z');
		glm::mat4 Soc = roml::scale(glm::mat4(1.0f), scale);

		return Loc * Rot * Soc;
	}


	virtual glm::vec3 findWorldPos(glm::mat4 mat, glm::vec3 pos) {
		return mat * glm::vec4(pos, 1.0f);
	}

	virtual void draw(Game* game) {
		glm::mat4 model = getModelMatrix();
		glm::vec4 color = game->lights[0]->color;
		glm::vec3 position = game->lights[0]->position;

		game->shaders[0]->Activate();

		glUniformMatrix4fv(glGetUniformLocation(game->shaders[0]->ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(game->shaders[0]->ID, "lightColor"), color.x, color.y, color.z, color.w);
		glUniform3f(glGetUniformLocation(game->shaders[0]->ID, "lightPos"), position.x, position.y, position.z);
		mesh.Draw(*game->shaders[0], *game->cameras[0]);
	}
};

