
#include "game.h"

Game::Game() {
	lastTime = glfwGetTime();
	this->gameWindow = gameWindow;
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