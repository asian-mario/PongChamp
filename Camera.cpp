#include"Camera.h"

Camera::Camera(int width, int height, glm::vec3 position) {
	Camera::width = width;
	Camera::height = height;
	Position = position;
}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane) {
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = roml::lookAt(Position, Position + Orientation, Up);
	projection = roml::createPerspective(roml::radians(FOVdeg), (float)(width / height), nearPlane, farPlane);

	cameraMatrix = projection * view;
}

void Camera::Matrix(Shader& shader, const char* uniform) {
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

