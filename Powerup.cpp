#include "Powerup.h"


void PowerupSpawn::update(Game* g) {
	if (!maxSpawn) {
		string powerups[3] = { "BallPlus", "PaddlePlus", "PaddleMinus" };
		string currentPowerup = powerups[rand() % 3];

		
		cout << currentPowerup << endl;
		if (currentPowerup == powerups[0]) {
			BallPlus(g);
		}
	}

}

Powerup::Powerup(glm::vec3 position, glm::vec3 scale, glm::vec3 velocity) {
	this->position = glm::vec3(position);
	this->scale = glm::vec3(scale);
	this->velocity = glm::vec3(velocity);
}

BallPlus::BallPlus(Game* g) {

	Powerup Power(position, scale, velocity);
	Power.mesh = Mesh(g->vertVec[0], g->indexVec[0], g->texturesVec[0]);

	glm::mat4 model = getModelMatrix();
	glm::vec4 lightCol = g->lights[0]->color;
	glm::vec3 lightPosition = g->lights[0]->position;

	g->shaders[0]->Activate();

	glUniformMatrix4fv(glGetUniformLocation(g->shaders[0]->ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniform4f(glGetUniformLocation(g->shaders[0]->ID, "lightColor"), lightCol.x, lightCol.y, lightCol.z, lightCol.w);
	glUniform3f(glGetUniformLocation(g->shaders[0]->ID, "lightPos"), lightPosition.x, lightPosition.y, lightPosition.z);
	Power.mesh.Draw(*g->shaders[0], *g->cameras[0]);



	bool intersect = g->balls[0]->circintersects(g->balls[0]->position, position, g->balls[0]->rad, 2.0, 2.0);

	if (intersect) {
		g->balls[0]->rad = 9.0f;
		g->balls[0]->scale = g->balls[0]->scale * 1.1f;

		maxSpawn = false;
	}


}

