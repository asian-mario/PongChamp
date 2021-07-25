#pragma once

class gameFont {
public:
	glm::mat4 ortho;
	glm::vec3 pos;
	gameFont(glm::mat4 ortho, glm::vec3 pos);
	void draw(Game* g, GLFWwindow* window, Font* font, const char* string);
};