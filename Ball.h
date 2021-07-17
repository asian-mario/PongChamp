#ifndef BALL_CLASS_H
#define BALL_CLASS_H

#include<iostream>
#include<stdlib.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "ROML.h"
#include <chrono>
#include <cmath>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>

class Ball {
	public:
		glm::vec3 scaleVec;
		glm::vec3 posVec;
		

		glm::vec3 speedVec;

		Ball(glm::vec3 posVec, glm::vec3 scalevec, glm::vec3 speedVec);
		glm::mat4 getModelMatrix();
};
#endif
