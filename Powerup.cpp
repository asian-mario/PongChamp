#include "Powerup.h"

void PowerupSpawn::resetPowerup() {
	currentPowerup = powerups[rand() % 3];
}

void PowerupSpawn::update(Game* g) {
	if (!maxSpawn) {

		cout << currentPowerup << endl;

		if (currentPowerup == powerups[0]) {
			spawn(g, 0);
		}

		if (currentPowerup == powerups[1]) {
			spawn(g, 0);
		}

		if (currentPowerup == powerups[2]) {
			spawn(g, 0);
		}

	

		maxSpawn = true;
	
	}

}

void PowerupSpawn::spawn(Game* g, int type) {

	switch (type) {
	case 0: 
		GameObject * p = new BallPlusPowerup(g, glm::vec3(rand() % 70, rand() % 90, 0.0f), glm::vec3(7.0f, 12.0f, 0.0f), glm::vec3(0.0f));


		g->gameObjects.push_back(p);
		
		
		break;

	}

	
}

BallPlusPowerup::BallPlusPowerup(Game* g, glm::vec3 position, glm::vec3 scale, glm::vec3 velocity) {
	this->position = glm::vec3(position);
	this->scale = glm::vec3(scale);
	this->velocity = glm::vec3(velocity);

	this->mesh = Mesh(g->vertVec[0], g->indexVec[0], g->texturesVec[0]);

}

void BallPlusPowerup::delayEffect(Game* g) {
	double dt = g->deltaTime;
	effect -= dt;

	if (effect <= 0.0 || g->balls[0]->position.x >= 95.0f || g->balls[0]->position.x <= -95.0f) {
		g->balls[0]->rad = 3.0f;
		g->balls[0]->scale = glm::vec3(9.6f, 19.1f, 0.0f);

		g->deleteObj(this);
	}
}

void BallPlusPowerup::update(Game* g) {
	if (!hit) {
		bool intersect = g->balls[0]->circintersects(g->balls[0]->position, position, g->balls[0]->rad, 6.5, 6.5);

		if (intersect) {
			g->balls[0]->rad = 4.0f;
			g->balls[0]->scale = g->balls[0]->scale * 2.0f;

			
			g->powerups[0]->currentPowerup = g->powerups[0]->powerups[rand() % 3];
			hit = true;
		}

		return;
	}

	delayEffect(g);
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

