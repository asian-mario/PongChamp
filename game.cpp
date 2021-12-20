
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

void Game::removeScreen(Screen* S) {
	for (auto c = ScreenObject.begin(); c != ScreenObject.end(); c++) {
		if (*c == S)
		{
			delete S;
			ScreenObject.erase(c);
			return;
		}
	}
}
void Game::update() {
	deltaTime = (float)glfwGetTime() - lastTime;
	lastTime = (float)glfwGetTime();

	for (GameObject* o : gameObjects)
		if (o != nullptr) {
			o->update(this);

			if (o->name != "" && debugSetting) {
				o->boundingBox = o->createBoundingBox();
			}
		}

	for (GameObject* p : particleSystems)
		p->update(this);

}

void Game::dtUpdate() {
	deltaTime = (float)glfwGetTime() - lastTime;
	lastTime = (float)glfwGetTime();
}

void Game::winReset(Game* g) {
	//-------------------------Win Check-------------------------------------
	if (g->texts[0]->score >= 5) {
		g->balls[0]->velocity = glm::vec3(0.0f);
		g->balls[0]->position = glm::vec3(0.0f);

		g->paddles[0]->lastHit = false;
		g->paddles[1]->lastHit = false;

		g->fonts[1]->drawString(600.0f, 450.0f, "PONG CHAMP", g->shaders[2]);
		g->fonts[1]->drawString(550.0f, 600.0f, "PLAYER 1 WINS!", g->shaders[2]);
		g->fonts[1]->drawString(550.0f, 800.0f, "RESTART? (Y/N)", g->shaders[2]);

		g->pause = true;





		if (glfwGetKey(g->gameWindow, GLFW_KEY_Y)) {
			g->texts[0]->score = 0;
			g->texts[1]->score = 0;
			//Position & Velocity Reset
			g->balls[0]->position = glm::vec3(-0.02f, 0.0f, 0.0f);
			g->paddles[0]->position = glm::vec3(-85.0f, 0.0f, 0.0f);
			g->paddles[1]->position = glm::vec3(85.0f, 0.0f, 0.0f);
			g->paddles[0]->velocity = glm::vec3(0.0f);
			g->paddles[1]->velocity = glm::vec3(0.0f);
			g->balls[0]->velocity = glm::vec3(-65.0f, 0.0f, 0.0f);

			g->pause = false;
		}
		if (glfwGetKey(g->gameWindow, GLFW_KEY_N)) {
			glfwSetWindowShouldClose(g->gameWindow, GL_TRUE);
		}
	}

	if (g->texts[1]->score >= 5) {
		g->balls[0]->velocity = glm::vec3(0.0f);
		g->balls[0]->position = glm::vec3(0.0f);

		g->paddles[0]->lastHit = false;
		g->paddles[1]->lastHit = false;

		g->fonts[1]->drawString(600.0f, 450.0f, "PONG CHAMP", g->shaders[2]);
		g->fonts[1]->drawString(550.0f, 600.0f, "PLAYER 2 WINS!", g->shaders[2]);
		g->fonts[1]->drawString(550.0f, 800.0f, "RESTART? (Y/N)", g->shaders[2]);
		g->pause = true;

		if (glfwGetKey(g->gameWindow, GLFW_KEY_Y)) {
			g->texts[0]->score = 0;
			g->texts[1]->score = 0;
			//Position & Velocity Reset
			g->balls[0]->position = glm::vec3(-0.02f, 0.0f, 0.0f);
			g->paddles[0]->position = glm::vec3(-85.0f, 0.0f, 0.0f);
			g->paddles[1]->position = glm::vec3(85.0f, 0.0f, 0.0f);
			g->paddles[0]->velocity = glm::vec3(0.0f);
			g->paddles[1]->velocity = glm::vec3(0.0f);
			g->balls[0]->velocity = glm::vec3(65.0f, 0.0f, 0.0f);

			g->pause = false;
		}
		if (glfwGetKey(g->gameWindow, GLFW_KEY_N)) {
			glfwSetWindowShouldClose(g->gameWindow, GL_TRUE);
		}
	}
	//-------------------------Win Check-------------------------------------
}

void Game::gameReset(Game* g) {
	g->texts[0]->score = 0;
	g->texts[1]->score = 0;
	//Position & Velocity Reset
	g->balls[0]->position = glm::vec3(-0.02f, 0.0f, 0.0f);
	g->paddles[0]->position = glm::vec3(-85.0f, 0.0f, 0.0f);
	g->paddles[1]->position = glm::vec3(85.0f, 0.0f, 0.0f);
	g->paddles[0]->velocity = glm::vec3(0.0f);
	g->paddles[1]->velocity = glm::vec3(0.0f);
	g->balls[0]->velocity = glm::vec3(65.0f, 0.0f, 0.0f);
}

void Game::updateScreen() {
	for (Screen* o : ScreenObject)
		if (o != nullptr)
			o->updateScreen(this);


}


void Game::draw() {
	for (GameObject* o : gameObjects)
		if (o != nullptr)
			o->draw(this);
}

void Game::drawScreen() {
	for (Screen* o : ScreenObject)
		if (o != nullptr)
			o->drawScreen(this);
}

