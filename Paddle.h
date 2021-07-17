#ifndef PADDLE_CLASS_H
#define PADDLE_CLASS_H

#include<iostream>
#include<stdlib.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "ROML.h"
#include <chrono>
#include <cmath>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>

class Paddle {
	public:
		glm::vec3 scaleVec;
		glm::vec3 posVec;
		glm::vec3 rotVec;

		enum CONTROLTYPE { WASD, ARROW };
		CONTROLTYPE type;

		Paddle(glm::vec3 posVec, glm::vec3 rotVec, glm::vec3 scaleVec, CONTROLTYPE type);

		glm::mat4 getModelMatrix();
		void Update(GLFWwindow* window);
};

#endif