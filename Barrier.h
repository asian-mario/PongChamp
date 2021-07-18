#ifndef BARRIER_CLASS_H
#define BARRIER_CLASS_H

#include <glm/glm.hpp>
#include "GameObject.h"
#include <vector>
#include "Paddle.h"
#include "game.h"

class Barrier : public GameObject {
	public:

		Barrier(glm::vec3 pos, glm::vec3 scale);

};
#endif 
