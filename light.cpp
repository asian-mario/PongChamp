#include "light.h"

Light::Light(glm::vec4 colorVec, glm::vec3 posVec) {

	this->colorVec = colorVec;
	this->posVec = posVec;

}

glm::mat4 Light::getModelMatrix() {
	glm::mat4 Loc = roml::translate(glm::mat4(1.0f), posVec);

	return Loc;
}