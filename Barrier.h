#pragma once

class Game;
#include "game.h"
#include <glm/glm.hpp>
#include <vector>
#include "GameObject.h"
#include "Paddle.h"


class Barrier : public GameObject {
	public:

		Barrier(glm::vec3 pos, glm::vec3 scale);


};

