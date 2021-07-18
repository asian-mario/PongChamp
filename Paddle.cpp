#include "Paddle.h"

Paddle::Paddle(glm::vec3 posVec, glm::vec3 rotVec, glm::vec3 scaleVec, CONTROLTYPE type, double velocity) {
	this->posVec = glm::vec3(posVec);
	this->rotVec = glm::vec3(rotVec);
	this->scaleVec = glm::vec3(scaleVec);
	this->type = type;
	this->velocity = velocity;
} 

glm::mat4 Paddle::getModelMatrix() {
	glm::mat4 Loc = roml::translate(glm::mat4(1.0f), posVec);
	glm::mat4 Soc = roml::scale(glm::mat4(1.0f), scaleVec);


	glm::mat4 rotX = roml::rotate(glm::mat4(1.0f), roml::radians(rotVec.x), 'X');
	glm::mat4 rotY = roml::rotate(glm::mat4(1.0f), roml::radians(rotVec.y), 'Y');
	glm::mat4 rotZ = roml::rotate(glm::mat4(1.0f), roml::radians(rotVec.z), 'Z');

	glm::mat4 Rot = rotZ * rotY * rotX;


	return Loc * Rot * Soc;
}

void Paddle::Update(GLFWwindow* window) {
	if (type == WASD) {
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			if (posVec.y >= 0.73f) {
				posVec.y += 0.0f;
			}
			if (posVec.y < 0.73f) {
				posVec.y += 0.01f;
				velocity += 0.0001;
			}
		}
		else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE) {
			velocity = 0.0;

		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			if (posVec.y <= -0.73f) {
				posVec.y -= 0.0f;
			}
			if (posVec.y > -0.73f) {
				posVec.y -= 0.01f;
				velocity -= 0.0001;
			}
		}
		else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE) {
			velocity = 0.0;
		}
	}

	if (type == ARROW) {
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
			if (posVec.y >= 0.73f) {
				posVec.y += 0.0f;
			}
			if (posVec.y < 0.73f) {
				posVec.y += 0.01f;
				velocity += 0.0001;
			}
		}
		else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_RELEASE) {
			velocity = 0.0;
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
			if (posVec.y <= -0.73f) {
				posVec.y -= 0.0f;
			}
			if (posVec.y > -0.73f) {
				posVec.y -= 0.01f;
				velocity -= 0.0001;
			}
		}
		else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_RELEASE) {
			velocity = 0.0;
		}
	}
}