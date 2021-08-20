
#include "Paddle.h"

Paddle::Paddle(glm::vec3 position, glm::vec3 scale, CONTROLTYPE type, glm::vec3 velocity) {
	this->position = glm::vec3(position);
	this->rotation = glm::vec3(0.0f);
	this->scale = glm::vec3(scale);
	this->type = type;
	this->velocity = glm::vec3(velocity);
} 


void Paddle::update(Game* g) {
	if (type == WASD) {
		if (glfwGetKey(g->gameWindow, GLFW_KEY_W) == GLFW_PRESS) {
			velocity.y = 110.0f;
		}
		else if (glfwGetKey(g->gameWindow, GLFW_KEY_S) == GLFW_PRESS) {
			velocity.y = -110.0f;
		}
	}

	if (type == ARROW) {
		if (glfwGetKey(g->gameWindow, GLFW_KEY_UP) == GLFW_PRESS) {
			velocity.y = 110.0f;
		}
		else if (glfwGetKey(g->gameWindow, GLFW_KEY_DOWN) == GLFW_PRESS) {
			velocity.y = -110.0f;
		}
	}

	if (velocity.y != 0)
		velocity.y += (velocity.y < 0 ? 1.0f : -1.0f) * decayControl * (float) g->deltaTime;

	if (abs(velocity.y) <= 0.05f) velocity.y = 0; //Stops paddle from stuttering at low speeds

	float deltaTime = g->deltaTime;
	
	if (position.y > 90.0f) {
		position.y = 90.0f;
		if (velocity.y > 0) velocity.y = -velocity.y;
	}

	if (position.y < -90.0f) {
		position.y = -90.0f;
		if (velocity.y < 0) velocity.y = -velocity.y;
	}

	position += velocity * deltaTime;
}

