#include "Powerup.h"

void PowerupSpawn::update(Game* g) {
	if (!maxSpawn) {

		cout << currentPowerup << endl;

		spawn(g, 0);

		maxSpawn = true;
	
	}

}

void PowerupSpawn::spawn(Game* g, int type) {

	switch (type) {
	case 0: 
		GameObject * p = new BallPlusPowerup(g, glm::vec3(rand() % 80, rand() % 90, 0.0f), glm::vec3(7.0f, 12.0f, 0.0f), glm::vec3(0.0f));

		g->gameObjects.push_back(p);
		break;

	}

	
}

BallPlusPowerup::BallPlusPowerup(Game* g, glm::vec3 position, glm::vec3 scale, glm::vec3 velocity) {
	this->position = glm::vec3(position);
	this->scale = glm::vec3(scale);
	this->velocity = glm::vec3(velocity);

	this->mesh = Mesh(g->vertVec[0], g->indexVec[0], g->texturesVec[3]);

}

void BallPlusPowerup::update(Game* g) {
	if (!hit) {
		bool intersect = g->balls[0]->circintersects(g->balls[0]->position, position, g->balls[0]->rad, 5.5, 5.5);

		if (intersect) {
			g->balls[0]->rad = 4.0f;
			g->balls[0]->scale = g->balls[0]->scale * 2.0f;

			hit = true;
		}

		return;
	}

}

void BallPlusPowerup::draw(Game* g) {
	if (hit) return;
	glm::mat4 model = getModelMatrix();
	glm::vec4 lightCol = g->lights[0]->color;
	glm::vec3 lightPosition = g->lights[0]->position;

	g->shaders[0]->Activate();

	glUniformMatrix4fv(glGetUniformLocation(g->shaders[0]->ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniform4f(glGetUniformLocation(g->shaders[0]->ID, "lightColor"), lightCol.x, lightCol.y, lightCol.z, lightCol.w);
	glUniform3f(glGetUniformLocation(g->shaders[0]->ID, "lightPos"), lightPosition.x, lightPosition.y, lightPosition.z);
	mesh.Draw(*g->shaders[0], *g->cameras[0]);
}

