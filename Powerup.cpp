#include "Powerup.h"

Powerup::Powerup(glm::vec3 position, glm::vec3 scale, glm::vec3 velocity) {
	this->position = glm::vec3(position);
	this->scale = glm::vec3(scale);
	this->velocity = glm::vec3(velocity);
}

void Powerup::update(Game* g) {
	string powerups[3] = { "BallPlus", "PaddlePlus", "PaddleDown" };
	string currentPowerup = powerups[rand() % 3];

	if (currentPowerup == powerups[1]) {
		BallPlus(g);
	}
}


void Powerup::BallPlus(Game* g) {
	if (maxSpawn == false) {

		Powerup Power(scale, scale, velocity);
		Power.mesh = Mesh(g->vertVec[0], g->indexVec[0], g->texturesVec[0]);

		glm::mat4 model = getModelMatrix();
		glm::vec4 color = g->lights[0]->color;
		glm::vec3 position = g->lights[0]->position;

		g->shaders[0]->Activate();

		glUniformMatrix4fv(glGetUniformLocation(g->shaders[0]->ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(g->shaders[0]->ID, "lightColor"), color.x, color.y, color.z, color.w);
		glUniform3f(glGetUniformLocation(g->shaders[0]->ID, "lightPos"), position.x, position.y, position.z);
		mesh.Draw(*g->shaders[0], *g->cameras[0]);

		maxSpawn = true;
	}

	bool intersect = g->balls[0]->circintersects(g->balls[0]->position, position, g->balls[0]->rad);

	if (intersect) {
		g->balls[0]->rad = 9.0f;
		g->balls[0]->scale = g->balls[0]->scale * 1.1f;

		maxSpawn = false;
	}
}

