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

void Camera::Inputs(GLFWwindow* window) {

	//Detecting a keypress and editing the camera's matrix to appropriate with it
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		Position += speed * (Orientation / 5.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		(Position += speed * -roml::normalize(roml::cross(Orientation, Up)) / 5.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		Position += speed * -(Orientation / 5.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		(Position += speed * roml::normalize(roml::cross(Orientation, Up)) / 5.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		Position += speed * (Up / 5.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		Position += speed * -(Up / 5.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		speed = 0.4f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
		speed = 0.1f;
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		//prevents it from jumping on click
		if (firstClick) {
			glfwSetCursorPos(window, (width / 2), (height / 2));
			firstClick = false;
		}

		double mouseX;
		double mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY); //filling our variables

		//Make sure it starts in the middle
		float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
		float rotY = sensitivity * (float)(mouseX - (height / 2)) / height;

		glm::vec3 newOrientation = roml::rotate(Orientation, roml::radians(-rotX), roml::normalize(roml::cross(Orientation, Up)));
		
		//Reset orientation for preventing a barell roll
		if (!((roml::angle(newOrientation, Up) <= roml::radians(5.0f)) or (roml::angle(newOrientation, -Up) <= roml::radians(5.0f)))) {
			Orientation = newOrientation;
		}

		Orientation = roml::rotate(Orientation, roml::radians(-rotY), Up);
		//Resetting cursor to the center of the window
		glfwSetCursorPos(window, (width / 2), (height / 2));
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_RELEASE) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstClick = true;
	}
}