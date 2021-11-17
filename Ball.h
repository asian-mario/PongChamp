#pragma once


#include "GameObject.h"
#include "game.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class Game;

class Ball : public GameObject {
	public:
		double control = 2500.0;
		const float maxSpeed = 200.0f;
		double rad;
		double decreaseVal = 0.85;
		bool limitSpeed = true;

		glm::vec4 color;

		Ball(std::string name, glm::vec3 pos, glm::vec3 scale, double rad, glm::vec3 velocity = glm::vec3(-0.005f, rand() / 10000000.0f, 0.0f));
		bool circintersects(glm::vec3 circle, glm::vec3 rect, double circleRadius, double width, double height);
		bool boundsCheck(glm::vec3 position, glm::vec3 velocity, float bounds);
		bool boundsCheckL(glm::vec3 position, glm::vec3 velocity, float bounds);
		void update(Game* g) override;
		
};

