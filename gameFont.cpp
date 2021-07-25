#include <GLFW/glfw3.h>
#include "game.h"
#include "gameFont.h"

gameFont::gameFont(glm::vec3 pos) {
	this->pos = glm::vec3(pos);
	this->scorestr = to_string(score);
	this->text = scorestr.c_str();
}

void gameFont::update(Game* g, GLFWwindow* window) {
	scorestr = to_string(score);
	text = scorestr.c_str();


	//-------------------------Win Check-------------------------------------
	if (g->texts[0]->score >= 5) {
		g->fonts[0]->drawString(600.0f, 450.0f, "PONG CHAMP", g->shaders[2]);
		g->pause = true;
		g->fonts[0]->drawString(550.0f, 600.0f, "PLAYER 1 WINS!", g->shaders[2]);
		g->fonts[0]->drawString(550.0f, 800.0f, "RESTART? (Y/N)", g->shaders[2]);
		if (glfwGetKey(g->gameWindow, GLFW_KEY_Y)) {
			g->pause = false;
			//Position & Velocity Reset
			g->texts[0]->score = 0;
			g->texts[1]->score = 0;
			g->balls[0]->position = glm::vec3(-0.02f, 0.0f, 0.0f);
			g->paddles[0]->position = glm::vec3(-85.0f, 0.0f, 0.0f);
			g->paddles[1]->position = glm::vec3(85.0f, 0.0f, 0.0f);
			g->paddles[0]->velocity = glm::vec3(0.0f);
			g->paddles[1]->velocity = glm::vec3(0.0f);
			g->balls[0]->velocity = glm::vec3(-65.0f, 0.0f, 0.0f);
		}
		if (glfwGetKey(g->gameWindow, GLFW_KEY_N)) {
			glfwWindowShouldClose(window) == 0;
		}
	}

	if (g->texts[1]->score >= 5) {
		g->fonts[0]->drawString(600.0f, 450.0f, "PONG CHAMP", g->shaders[2]);
		g->pause = true;
		g->fonts[0]->drawString(550.0f, 600.0f, "PLAYER 2 WINS!", g->shaders[2]);
		g->fonts[0]->drawString(550.0f, 800.0f, "RESTART? (Y/N)", g->shaders[2]);
		if (glfwGetKey(g->gameWindow, GLFW_KEY_Y)) {
			g->pause = false;
			//Position & Velocity Reset
			g->texts[0]->score = 0;
			g->texts[1]->score = 0;
			g->balls[0]->position = glm::vec3(-0.02f, 0.0f, 0.0f);
			g->paddles[0]->position = glm::vec3(-85.0f, 0.0f, 0.0f);
			g->paddles[1]->position = glm::vec3(85.0f, 0.0f, 0.0f);
			g->paddles[0]->velocity = glm::vec3(0.0f);
			g->paddles[1]->velocity = glm::vec3(0.0f);
			g->balls[0]->velocity = glm::vec3(65.0f, 0.0f, 0.0f);
		}
		if (glfwGetKey(g->gameWindow, GLFW_KEY_N)) {
			glfwWindowShouldClose(window) == 0;
		}
	}
	//-------------------------Win Check-------------------------------------

}