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

		enum CONTROLTYPE { WASD, ARROW };
		CONTROLTYPE type;

		Paddle(glm::vec3 position, glm::vec3 scale, CONTROLTYPE type, glm::vec3 velocity);
		void update(Game* g) override;
};

