#ifndef BARRIER_CLASS_H
#define BARRIER_CLASS_H

#include<iostream>
#include<stdlib.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "ROML.h"
#include <chrono>
#include <cmath>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>

class Barrier {
	public:
		glm::vec3 posVec;
		glm::vec3 scaleVec;


		Barrier(glm::vec3 posvec, glm::vec3 scaleVec);
		glm::mat4 getModelMatrix();

};
#endif 
