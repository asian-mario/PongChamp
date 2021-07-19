#pragma once
#ifndef PADDLE_CLASS_H
#define PADDLE_CLASS_H

#include "game.h"
#include <glm/glm.hpp>
#include <vector>
#include "GameObject.h"

#include "shaderclass.h"
#include "Camera.h"




class Paddle : public GameObject {
	public:


		enum CONTROLTYPE { WASD, ARROW };
		CONTROLTYPE type;

		Paddle(glm::vec3 position, glm::vec3 scale, CONTROLTYPE type, glm::vec3 velocity);

		void update(Game* g, GLFWwindow* gameWindow);
	
};

#endif