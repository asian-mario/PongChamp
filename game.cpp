#include "game.h"

Game::Game() {

}

void Game::update() {
	for (GameObject o : gameObjects)
		o.update();
}