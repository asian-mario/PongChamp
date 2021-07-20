#pragma once

class GameObject;
class Game;

#include "GameObject.h"
#include "game.h"

#include <glm/glm.hpp>
#include <vector>






class Paddle : public GameObject {
	public:


		enum CONTROLTYPE { WASD, ARROW };
		CONTROLTYPE type;

		Paddle(glm::vec3 position, glm::vec3 scale, CONTROLTYPE type, glm::vec3 velocity);

		void update(Game* g, GLFWwindow* gameWindow);
	
};

