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
}

void miscFont::smashDraw(Game* g) {

	if (timer > 0) {
		g->fonts[1]->drawString(550.0f, 600.0f, "PONG SMASH!", g->shaders[2]);
		//g->slowMo(timer);

		timer -= 0.05;

	}	
}