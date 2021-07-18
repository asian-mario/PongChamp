#ifndef PADDLE_CLASS_H
#define PADDLE_CLASS_H

#include <glm/glm.hpp>
#include "GameObject.h"
#include <vector>
#include "Paddle.h"
#include "game.h"

class Paddle : public GameObject {
	public:


		enum CONTROLTYPE { WASD, ARROW };
		CONTROLTYPE type;

		Paddle(glm::vec3 position, glm::vec3 scale, CONTROLTYPE type);

		void update(Game* g, GLFWwindow* gameWindow);
};

#endif