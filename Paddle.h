#pragma once



#include "GameObject.h"
#include "game.h"
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include <vector>

class GameObject;
class Game;




class Paddle : public GameObject {
	public:
		bool lastHit = false;

		double width = 1.8;
		double height = 13.0;
		float decayControl = 200.0f;

		enum CONTROLTYPE { WASD, ARROW };
		CONTROLTYPE type;

		Paddle(glm::vec3 position, glm::vec3 scale, CONTROLTYPE type, glm::vec3 velocity, std::string name);
		void update(Game* g) override;
};

