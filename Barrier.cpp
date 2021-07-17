#include "Barrier.h"

Barrier::Barrier(glm::vec3 posVec, glm::vec3 scaleVec) {
	this->posVec = posVec;
	this->scaleVec = scaleVec;

}

glm::mat4 Barrier::getModelMatrix() {
	glm::mat4 Loc = roml::translate(glm::mat4(1.0f), posVec);
	glm::mat4 Soc = roml::scale(glm::mat4(1.0f), scaleVec);

	return Loc * Soc;
}