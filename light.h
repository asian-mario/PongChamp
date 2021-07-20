#pragma once

#include "GameObject.h"
#include <glm/glm.hpp>
#include <vector>

class GameObject;


class Light : public GameObject {
	public:

		Light(glm::vec4 color, glm::vec3 position);
		void draw(Game* g);

};


