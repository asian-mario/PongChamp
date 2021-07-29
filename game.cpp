
#include "game.h"

Game::Game() {
	lastTime = glfwGetTime();
	this->gameWindow = gameWindow;
}

void Game::update() {
	for (GameObject* o : gameObjects)
		o->update(this);
	for (GameObject* p : particleSystems)
		p->update(this);

	lastTime = (float) glfwGetTime();
}

void Game::draw() {
	for (GameObject* o : gameObjects)
		o->draw(this);
}

float Game::deltaTime() {
	// get time difference from last frame
	return (float) glfwGetTime() - lastTime;
}