#pragma once

class Game;

#include "game.h"
#include <glm/glm.hpp>
#include <vector>
#include "GameObject.h"
#include "Paddle.h"


class Light : public GameObject {
	public:

		Light(glm::vec4 color, glm::vec3 position);
		void draw(Game* g);

};


