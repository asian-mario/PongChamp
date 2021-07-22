#pragma once


#include "GameObject.h"
#include "game.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class Game;

class Ball : public GameObject {
	public:
		double control = 1000.0;

		Ball(glm::vec3 pos, glm::vec3 scale, glm::vec3 velocity = glm::vec3(-0.005f, rand() / 10000000.0f, 0.0f));
		bool circintersects(glm::vec3 circle, glm::vec3 rect, double circleRadius);
		bool boundsCheck(glm::vec3 position, glm::vec3 velocity, float bounds);
		bool boundsCheckL(glm::vec3 position, glm::vec3 velocity, float bounds);
		void update(Game* g) override;
		
};

