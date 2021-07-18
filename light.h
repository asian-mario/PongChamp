#ifndef LIGHT_CLASS_H
#define LIGHT_CLASS_H

#include <glm/glm.hpp>
#include "GameObject.h"
#include <vector>
#include "Paddle.h"
#include "game.h"

class Light : public GameObject {
	public:
		glm::vec4 colorVec;

		Light(glm::vec4 colorVec, glm::vec3 pos);

};

#endif 
