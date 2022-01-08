#include "GameObject.h"
#include "game.h"
#include "Camera.h"
#include "shaderclass.h"

glm::mat4 GameObject::getModelMatrix() {
	glm::mat4 Loc = roml::translate(glm::mat4(1.0f), position);
	glm::mat4 Rot = roml::rotate(glm::mat4(1.0f), rotation.x, 'X') * roml::rotate(glm::mat4(1.0f), rotation.y, 'Y') * roml::rotate(glm::mat4(1.0f), rotation.z, 'Z');
	glm::mat4 Soc = roml::scale(glm::mat4(1.0f), scale);

	return Loc * Rot * Soc;
}

glm::vec3 GameObject::findWorldPos() {
	return getModelMatrix() * glm::vec4(1.0f);
}

//AABB because its easier to implement
glm::vec4 GameObject::createBoundingBox() {
	glm::vec4 boundingBox = glm::vec4(1.0f);

	//RIGHT
	boundingBox.x = position.x + scale.x;
	//LEFT
	boundingBox.y = position.x - scale.x;
	//UP
	boundingBox.z = position.y + scale.y;
	//DOWN							   
	boundingBox.w = position.y - scale.y;

	return boundingBox;
}

void GameObject::draw(Game* game) {
	glm::mat4 model = getModelMatrix();
	glm::vec4 color = game->lights[0]->color;
	glm::vec3 position = game->lights[0]->position;

	game->shaders[0]->Activate();

	glUniformMatrix4fv(glGetUniformLocation(game->shaders[0]->ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniform4f(glGetUniformLocation(game->shaders[0]->ID, "lightColor"), color.x, color.y, color.z, color.w);
	glUniform3f(glGetUniformLocation(game->shaders[0]->ID, "lightPos"), position.x, position.y, position.z);
	mesh.Draw(*game->shaders[0], *game->cameras[0]);
}