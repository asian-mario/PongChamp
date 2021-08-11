#pragma once

#include<iostream>
#include<stdlib.h>
#include<string>
#include <glad/glad.h>
#include<glm/glm.hpp>


#include "GameObject.h"
class Game;
class GameObject;
class GLFWwindow;

using namespace std;

class gameFont : public GameObject{
public:
	int score = 0;
	glm::vec3 pos;
	string scorestr;
	const char* text;
	

	gameFont(glm::vec3 pos);
	void update(Game* g, GLFWwindow* window);

};

class miscFont : public GameObject {
public:
	float timer = 5.0f;
	void smashDraw(Game* g);
};