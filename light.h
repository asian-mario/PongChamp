#pragma once

class GameObject;
class Game;
class Paddle;

#include "GameObject.h"
#include "game.h"
#include <glm/glm.hpp>
#include <vector>
#include "Paddle.h"


class Light : public GameObject {
	public:

		Light(glm::vec4 color, glm::vec3 position);
		void draw(Game* g);

};


