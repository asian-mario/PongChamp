#ifndef LIGHT_CLASS_H
#define LIGHT_CLASS_H

#include<iostream>
#include<stdlib.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "ROML.h"
#include <chrono>
#include <cmath>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>

class Light {
	public:
		glm::vec4 colorVec;
		glm::vec3 posVec;

		

		Light(glm::vec4 colorVec, glm::vec3 posVec);

		glm::mat4 getModelMatrix();
};

#endif 
