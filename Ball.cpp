#include "Ball.h"

Ball::Ball(glm::vec3 posVec, glm::vec3 scaleVec, glm::vec3 speedVec) {
	this->posVec = posVec;
	this->scaleVec = scaleVec;
	this->speedVec = speedVec;

}

glm::mat4 Ball::getModelMatrix() {
	glm::mat4 Loc = roml::translate(glm::mat4(1.0f), posVec);
	glm::mat4 Soc = roml::scale(glm::mat4(1.0f), scaleVec);

	return Loc * Soc;
}