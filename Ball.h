#pragma once

class Game;
#include "GameObject.h"
#include "game.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Paddle.h"


class Ball : public GameObject {
	public:

		Ball(glm::vec3 pos, glm::vec3 scale, glm::vec3 velocity = glm::vec3(-0.005f, rand() / 10000000.0f, 0.0f));
		void update(Game* g);
		bool circintersects(glm::vec3 circle, glm::vec3 rect, double circleRadius);
};

