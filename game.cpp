#include "game.h"

Game::Game() {
	lastTime = glfwGetTime();
	this->gameWindow = gameWindow;
}

void Game::update() {
	for (GameObject* o : gameObjects)
		o->update(this);
	lastTime = glfwGetTime();
}

void Game::draw() {
	for (GameObject* o : gameObjects)
		o->draw(this);
}

double Game::deltaTime() {
	// get time difference from last frame
	return glfwGetTime() - lastTime;
}