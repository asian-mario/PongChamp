#pragma once

#include<iostream>
#include<stdlib.h>
#include<string>
#include <glad/glad.h>
#include<glm/glm.hpp>


class Game;
class GLFWwindow;

using namespace std;

class gameFont{
public:
	int score = 0;
	glm::vec3 pos;
	string scorestr;
	const char* text;
	bool endGame = false;

	gameFont(glm::vec3 pos);
	void update(Game* g, GLFWwindow* window);
};