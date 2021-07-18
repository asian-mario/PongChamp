#include "game.h"

Game::Game(GLFWwindow* gameWindow) {
	lastTime = glfwGetTime();
	this->gameWindow = gameWindow;
}

void Game::update() {
	for (GameObject* o : gameObjects)
		o->update(this);
	lastTime = glfwGetTime();
}

double Game::deltaTime() {
	// get time difference from last frame
	return glfwGetTime() - lastTime;
}