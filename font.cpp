#include "game.h"
#include <GLFW/glfw3.h>

#include"font.h"

gameFont::gameFont(glm::mat4 ortho, glm::vec3 pos) {
	this->ortho = glm::mat4(ortho);
	this->pos = glm::vec3(pos);
}

void gameFont::draw(Game* g, GLFWwindow* window, Font* font, const char* string) {
	g->shaders[2]->Activate();

	int w, h;
	glfwGetWindowSize(window, &w, &h);

	glUniformMatrix4fv(glGetUniformLocation(g->shaders[2]->ID, "ModViewProj"), 1, GL_FALSE, &ortho[0][0]);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	font->drawString(pos.x, pos.y, string, g->shaders[2]);

}