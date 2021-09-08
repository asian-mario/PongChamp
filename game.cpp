
#include "game.h"

Game::Game() {
	lastTime = glfwGetTime();
	this->gameWindow = gameWindow;
}

bool Game::timer(int time) {
	if (time > 0) {
		time--;
	}

	if (time <= 0) {
		return true;
	}
}

void Game::slowMo(float time) {
	time -= deltaTime;

	if (time > 0) {
		for (GameObject* o : gameObjects)
			o->velocity = glm::vec3(1.0f);
	}
}

void Game::deleteObj(GameObject* GO) {	
	for (auto c = gameObjects.begin(); c != gameObjects.end(); c++) {
		if (*c == GO)
		{
			delete GO;
			gameObjects.erase(c);
			return;
		}
	}
}
void Game::update() {
	deltaTime = (float)glfwGetTime() - lastTime;
	lastTime = (float)glfwGetTime();
	for (GameObject* o : gameObjects)
		if (o != nullptr)
			o->update(this);

	for (GameObject* p : particleSystems)
		p->update(this);


	
}

void Game::draw() {
	for (GameObject* o : gameObjects)
		if (o != nullptr)
			o->draw(this);
}