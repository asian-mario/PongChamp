#pragma once


#include "GameObject.h"
#include <glm/glm.hpp>
#include <vector>

class GameObject;

class Barrier : public GameObject {
	public:
		bool barrierHit = false;

		Barrier(glm::vec3 pos, glm::vec3 scale);
};

