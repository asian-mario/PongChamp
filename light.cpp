#include "light.h"

Light::Light(glm::vec4 color, glm::vec3 position) {

	this->color = glm::vec4(color);
	this->position = glm::vec3(position);

}

void Light::draw(Game* g) {
	glm::mat4 model = getModelMatrix();
	glm::vec3 position = position;
	glm::vec4 color = color;
	g->shaders[1]->Activate();

	glUniformMatrix4fv(glGetUniformLocation(g->shaders[1]->ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniform4f(glGetUniformLocation(g->shaders[1]->ID, "lightColor"), color.x, color.y, color.z, color.w);
	mesh.Draw(*g->shaders[1], *g->cameras[0]);
}