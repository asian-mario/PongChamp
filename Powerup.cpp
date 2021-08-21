#include "Powerup.h"

void PowerupSpawn::resetPowerup() {
	currentPowerup = powerups[rand() % 3];
}

void PowerupSpawn::deletePowerup(GameObject* GO) {
	for (GameObject*& g : activePowerup)
		if (GO == g)
		{
			g = nullptr;  
			activeSpwn--;
			resetPowerup();

			return;
		}
}
void PowerupSpawn::update(Game* g) {
	if (activeSpwn < maxSpawn) {

		cout << currentPowerup << endl;

		if (currentPowerup == powerups[0]) {
			spawn(g, 4);
		}

		if (currentPowerup == powerups[1]) {
			spawn(g, 4);
		}

		if (currentPowerup == powerups[2]) {
			spawn(g, 4);
		}

		if (currentPowerup == powerups[3]) {
			spawn(g, 4);
		}

		if (currentPowerup == powerups[4]) {
			spawn(g, 4);
		}
	
	}

}

void PowerupSpawn::spawn(Game* g, int type) {

	float dt = g->deltaTime;
	delay -= dt;

	switch (type) {
	case 0: 

		if (delay <= 0) {
			GameObject* newP = new BallPlusPowerup(g, glm::vec3(rand() % 65, rand() % 80, 0.0f), glm::vec3(7.0f, 12.0f, 0.0f), glm::vec3(0.0f));
			activeSpwn++;

			g->gameObjects.push_back(newP);
			this->activePowerup.push_back(newP);

			delay = 8.0f;
		}


		break;

	case 1:

		if (delay <= 0) {
			GameObject* newP = new PaddlePlusPowerup(g, glm::vec3(rand() % 65, rand() % 80, 0.0f), glm::vec3(7.0f, 12.0f, 0.0f), glm::vec3(0.0f));
			activeSpwn++;

			g->gameObjects.push_back(newP);
			this->activePowerup.push_back(newP);

			delay = 8.0f;
		}


		break;

	case 2:
		if (delay <= 0) {
			GameObject* newP = new PaddleMinusPowerup(g, glm::vec3(rand() % 65, rand() % 80, 0.0f), glm::vec3(7.0f, 12.0f, 0.0f), glm::vec3(0.0f));
			activeSpwn++;

			g->gameObjects.push_back(newP);
			this->activePowerup.push_back(newP);

			delay = 8.0f;
		}


		break;

	case 3:
		if (delay <= 0) {
			GameObject* newP = new ButterPowerup(g, glm::vec3(rand() % 65, rand() % 80, 0.0f), glm::vec3(7.0f, 12.0f, 0.0f), glm::vec3(0.0f));
			activeSpwn++;

			g->gameObjects.push_back(newP);
			this->activePowerup.push_back(newP);

			delay = 8.0f;
		}

	case 4:
		if (delay <= 0) {
			GameObject* newP = new UltraSmashPowerup(g, glm::vec3(rand() % 65, rand() % 80, 0.0f), glm::vec3(7.0f, 12.0f, 0.0f), glm::vec3(0.0f));
			activeSpwn++;

			g->gameObjects.push_back(newP);
			this->activePowerup.push_back(newP);

			delay = 8.0f;
		}
	}


	
}

//------------------------------------BallPlus-------------------------------------------------------
BallPlusPowerup::BallPlusPowerup(Game* g, glm::vec3 position, glm::vec3 scale, glm::vec3 velocity) {
	this->position = glm::vec3(position);
	this->scale = glm::vec3(scale);
	this->velocity = glm::vec3(velocity);

	this->mesh = Mesh(g->vertVec[0], g->indexVec[0], g->texturesVec[6]);

}

void BallPlusPowerup::delayEffect(Game* g) {
	double dt = g->deltaTime;
	effect -= dt;

	if (effect <= 0.0 || g->balls[0]->position.x >= 95.0f || g->balls[0]->position.x <= -95.0f) {
		g->balls[0]->rad = 3.0f;
		g->balls[0]->scale = glm::vec3(9.6f, 19.1f, 0.0f);

		g->PowerupSpawner[0]->deletePowerup(this);
		g->deleteObj(this);
	}
}

void BallPlusPowerup::update(Game* g) {
	if (!hit) {
		bool intersect = g->balls[0]->circintersects(g->balls[0]->position, position, g->balls[0]->rad, 7.5, 7.5);

		if (intersect) {
			g->balls[0]->rad = 4.0f;
			g->balls[0]->scale = g->balls[0]->scale * 2.0f;

			for (int i = 0; i < 25; i++) {
				g->particleSystems[0]->spawn(g, glm::vec3(position.x + 2.0f, position.y + 2.0f, 0.0f), glm::vec3(rand() / 400.0f, rand() / 400.0f, 0.0f), glm::vec3(2.0f), glm::vec4(1.0f), 1.0f);
			}

			hit = true;
		}

		return;
	}

	delayEffect(g);
}

void BallPlusPowerup::draw(Game* g) {
	if (hit) return;


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glm::mat4 model = getModelMatrix();
	glm::vec4 lightCol = g->lights[0]->color;
	glm::vec3 lightPosition = g->lights[0]->position;

	g->shaders[0]->Activate();

	glUniformMatrix4fv(glGetUniformLocation(g->shaders[0]->ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniform4f(glGetUniformLocation(g->shaders[0]->ID, "lightColor"), lightCol.x, lightCol.y, lightCol.z, lightCol.w);
	glUniform3f(glGetUniformLocation(g->shaders[0]->ID, "lightPos"), lightPosition.x, lightPosition.y, lightPosition.z);
	mesh.Draw(*g->shaders[0], *g->cameras[0]);
}

//-----------------------------------------------------------------------------------------------------

//----------------------------------------PaddlePlus---------------------------------------------------
PaddlePlusPowerup::PaddlePlusPowerup(Game* g, glm::vec3 position, glm::vec3 scale, glm::vec3 velocity) {
	this->position = glm::vec3(position);
	this->scale = glm::vec3(scale);
	this->velocity = glm::vec3(velocity);
	
	this->mesh = Mesh(g->vertVec[0], g->indexVec[0], g->texturesVec[7]);

}

void PaddlePlusPowerup::delayEffect(Game* g) {
	double dt = g->deltaTime;
	effect -= dt;

	if (effect <= 0.0) {
		g->paddles[0]->height = 12.0;
		g->paddles[0]->scale.y = 20.0f;

		g->PowerupSpawner[0]->deletePowerup(this);
		g->deleteObj(this);
	}
}

void PaddlePlusPowerup::update(Game* g) {
	if (!hit) {
		bool intersect = g->balls[0]->circintersects(g->balls[0]->position, position, g->balls[0]->rad, 7.5, 7.5);

		if (intersect && g->paddles[0]->lastHit) {
			g->paddles[0]->scale.y = 30.0f;
			g->paddles[0]->height = 18.0;

			for (int i = 0; i < 25; i++) {
				g->particleSystems[0]->spawn(g, glm::vec3(position.x + 2.0f, position.y + 2.0f, 0.0f), glm::vec3(rand() / 400.0f, rand() / 400.0f, 0.0f), glm::vec3(2.0f), glm::vec4(1.0f), 1.0f);
			}

			hit = true;
		}

		if (intersect && g->paddles[1]->lastHit) {
			g->paddles[1]->scale.y = 30.0f;
			g->paddles[1]->height = 18.0;

			for (int i = 0; i < 25; i++) {
				g->particleSystems[0]->spawn(g, glm::vec3(position.x + 2.0f, position.y + 2.0f, 0.0f), glm::vec3(rand() / 400.0f, rand() / 400.0f, 0.0f), glm::vec3(2.0f), glm::vec4(1.0f), 1.0f);
			}

			hit = true;
		}

		return;
	}

	delayEffect(g);
}

void PaddlePlusPowerup::draw(Game* g) {
	if (hit) return;


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glm::mat4 model = getModelMatrix();
	glm::vec4 lightCol = g->lights[0]->color;
	glm::vec3 lightPosition = g->lights[0]->position;

	g->shaders[0]->Activate();

	glUniformMatrix4fv(glGetUniformLocation(g->shaders[0]->ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniform4f(glGetUniformLocation(g->shaders[0]->ID, "lightColor"), lightCol.x, lightCol.y, lightCol.z, lightCol.w);
	glUniform3f(glGetUniformLocation(g->shaders[0]->ID, "lightPos"), lightPosition.x, lightPosition.y, lightPosition.z);
	mesh.Draw(*g->shaders[0], *g->cameras[0]);
}

//-----------------------------------------------------------------------------------------------------

//----------------------------------------PaddleMinus---------------------------------------------------
PaddleMinusPowerup::PaddleMinusPowerup(Game* g, glm::vec3 position, glm::vec3 scale, glm::vec3 velocity) {
	this->position = glm::vec3(position);
	this->scale = glm::vec3(scale);
	this->velocity = glm::vec3(velocity);

	this->mesh = Mesh(g->vertVec[0], g->indexVec[0], g->texturesVec[8]);

}

void PaddleMinusPowerup::delayEffect(Game* g) {
	double dt = g->deltaTime;
	effect -= dt;

	if (effect <= 0.0) {
		g->paddles[0]->height = 12.0;
		g->paddles[0]->scale.y = 20.0f;

		g->paddles[1]->height = 12.0;
		g->paddles[1]->scale.y = 20.0f;


		g->PowerupSpawner[0]->deletePowerup(this);
		g->deleteObj(this);
	}
}

void PaddleMinusPowerup::update(Game* g) {
	if (!hit) {
		bool intersect = g->balls[0]->circintersects(g->balls[0]->position, position, g->balls[0]->rad, 7.5, 7.5);

		if (intersect && g->paddles[0]->lastHit) {
			g->paddles[1]->scale.y = 10.0f;
			g->paddles[1]->height = 6.0;

			for (int i = 0; i < 25; i++) {
				g->particleSystems[0]->spawn(g, glm::vec3(position.x + 2.0f, position.y + 2.0f, 0.0f), glm::vec3(rand() / 400.0f, rand() / 400.0f, 0.0f), glm::vec3(2.0f), glm::vec4(1.0f), 1.0f);
			}

			hit = true;
		}

		if (intersect && g->paddles[1]->lastHit) {
			g->paddles[0]->scale.y = 10.0f;
			g->paddles[0]->height = 6.0;

			for (int i = 0; i < 25; i++) {
				g->particleSystems[0]->spawn(g, glm::vec3(position.x + 2.0f, position.y + 2.0f, 0.0f), glm::vec3(rand() / 400.0f, rand() / 400.0f, 0.0f), glm::vec3(2.0f), glm::vec4(1.0f), 1.0f);
			}

			hit = true;
		}

		return;
	}

	delayEffect(g);
}

void PaddleMinusPowerup::draw(Game* g) {
	if (hit) return;


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glm::mat4 model = getModelMatrix();
	glm::vec4 lightCol = g->lights[0]->color;
	glm::vec3 lightPosition = g->lights[0]->position;

	g->shaders[0]->Activate();

	glUniformMatrix4fv(glGetUniformLocation(g->shaders[0]->ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniform4f(glGetUniformLocation(g->shaders[0]->ID, "lightColor"), lightCol.x, lightCol.y, lightCol.z, lightCol.w);
	glUniform3f(glGetUniformLocation(g->shaders[0]->ID, "lightPos"), lightPosition.x, lightPosition.y, lightPosition.z);
	mesh.Draw(*g->shaders[0], *g->cameras[0]);
}

//-----------------------------------------------------------------------------------------------------
//----------------------------------------ButterFingers---------------------------------------------------
ButterPowerup::ButterPowerup(Game* g, glm::vec3 position, glm::vec3 scale, glm::vec3 velocity) {
	this->position = glm::vec3(position);
	this->scale = glm::vec3(scale);
	this->velocity = glm::vec3(velocity);

	this->mesh = Mesh(g->vertVec[0], g->indexVec[0], g->texturesVec[9]);

}

void ButterPowerup::delayEffect(Game* g) {
	double dt = g->deltaTime;
	effect -= dt;

	if (effect <= 0.0) {
		g->paddles[0]->decayControl = 200.0;
		g->paddles[1]->decayControl = 200.0;


		g->PowerupSpawner[0]->deletePowerup(this);
		g->deleteObj(this);
	}
}

void ButterPowerup::update(Game* g) {
	if (!hit) {
		bool intersect = g->balls[0]->circintersects(g->balls[0]->position, position, g->balls[0]->rad, 7.5, 7.5);

		if (intersect && g->paddles[0]->lastHit) {
			g->paddles[1]->decayControl = 75.0;

			for (int i = 0; i < 25; i++) {
				g->particleSystems[0]->spawn(g, glm::vec3(position.x + 2.0f, position.y + 2.0f, 0.0f), glm::vec3(rand() / 400.0f, rand() / 400.0f, 0.0f), glm::vec3(2.0f), glm::vec4(1.0f), 1.0f);
			}

			hit = true;
		}

		if (intersect && g->paddles[1]->lastHit) {
			g->paddles[0]->decayControl = 75.0;

			for (int i = 0; i < 25; i++) {
				g->particleSystems[0]->spawn(g, glm::vec3(position.x + 2.0f, position.y + 2.0f, 0.0f), glm::vec3(rand() / 400.0f, rand() / 400.0f, 0.0f), glm::vec3(2.0f), glm::vec4(1.0f), 1.0f);
			}

			hit = true;
		}

		return;
	}

	delayEffect(g);
}

void ButterPowerup::draw(Game* g) {
	if (hit) return;


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glm::mat4 model = getModelMatrix();
	glm::vec4 lightCol = g->lights[0]->color;
	glm::vec3 lightPosition = g->lights[0]->position;

	g->shaders[0]->Activate();

	glUniformMatrix4fv(glGetUniformLocation(g->shaders[0]->ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniform4f(glGetUniformLocation(g->shaders[0]->ID, "lightColor"), lightCol.x, lightCol.y, lightCol.z, lightCol.w);
	glUniform3f(glGetUniformLocation(g->shaders[0]->ID, "lightPos"), lightPosition.x, lightPosition.y, lightPosition.z);
	mesh.Draw(*g->shaders[0], *g->cameras[0]);
}
//----------------------------------------UltraSmash---------------------------------------------------
UltraSmashPowerup::UltraSmashPowerup(Game* g, glm::vec3 position, glm::vec3 scale, glm::vec3 velocity) {
	this->position = glm::vec3(position);
	this->scale = glm::vec3(scale);
	this->velocity = glm::vec3(velocity);

	this->mesh = Mesh(g->vertVec[0], g->indexVec[0], g->texturesVec[10]);

}

void UltraSmashPowerup::delayEffect(Game* g) {
	double dt = g->deltaTime;
	strHint -= dt;

	if (strHint > 0) {
		g->fonts[1]->drawString(700.0f, 1050.0f, "PRESS 'U'", g->shaders[2]);
	}

	if (glfwGetKey(g->gameWindow, GLFW_KEY_U)) {
		g->balls[0]->limitSpeed = false;
		exec = true;
	}


	if (exec == true) {
		effect -= dt;

		if (effect > 0) {
			g->fonts[1]->drawString(700.0f, 1050.0f, "ACTIVATED", g->shaders[2]);
		}

		if (effect <= 0.0) {
			g->balls[0]->limitSpeed = true;

			g->PowerupSpawner[0]->deletePowerup(this);
			g->deleteObj(this);
		}
	}
}

void UltraSmashPowerup::update(Game* g) {
	if (!hit) {
		bool intersect = g->balls[0]->circintersects(g->balls[0]->position, position, g->balls[0]->rad, 7.5, 7.5);

		if (intersect) {

			for (int i = 0; i < 25; i++) {
				g->particleSystems[0]->spawn(g, glm::vec3(position.x + 2.0f, position.y + 2.0f, 0.0f), glm::vec3(rand() / 400.0f, rand() / 400.0f, 0.0f), glm::vec3(2.0f), glm::vec4(1.0f), 1.0f);
			}

			position = glm::vec3(2000.0f, 2000.0f, 0.0f);
			hit = true;
		}


		return;
	}

	delayEffect(g);
}

void UltraSmashPowerup::draw(Game* g) {
	if (hit) return;


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glm::mat4 model = getModelMatrix();
	glm::vec4 lightCol = g->lights[0]->color;
	glm::vec3 lightPosition = g->lights[0]->position;

	g->shaders[0]->Activate();

	glUniformMatrix4fv(glGetUniformLocation(g->shaders[0]->ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniform4f(glGetUniformLocation(g->shaders[0]->ID, "lightColor"), lightCol.x, lightCol.y, lightCol.z, lightCol.w);
	glUniform3f(glGetUniformLocation(g->shaders[0]->ID, "lightPos"), lightPosition.x, lightPosition.y, lightPosition.z);
	mesh.Draw(*g->shaders[0], *g->cameras[0]);
}