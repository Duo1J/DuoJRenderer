#include "Camera.h"
#include "Input/Input.h"
#include <GLFW/glfw3.h>
#include <gtc/matrix_transform.hpp>

Camera::Camera()
{
	transform.front = glm::vec3(0, 0, 1);
	transform.up = glm::vec3(0, 1, 0);

	UpdateCameraVector();
}

Camera::Camera(Transform& _transform)
{
	transform = _transform;
	UpdateCameraVector();
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(transform.position, transform.position + transform.front, transform.up);
}

void Camera::ProcessKeyboardInput(float deltaTime)
{
	if (Input::GetKey(GLFW_KEY_W) == GLFW_PRESS)
	{
		transform.position += transform.front * moveSpeed * deltaTime;
	}
	if (Input::GetKey(GLFW_KEY_S) == GLFW_PRESS)
	{
		transform.position -= transform.front * moveSpeed * deltaTime;
	}
	if (Input::GetKey(GLFW_KEY_A) == GLFW_PRESS)
	{
		transform.position -= glm::normalize(glm::cross(transform.front, transform.up)) * moveSpeed * deltaTime;
	}
	if (Input::GetKey(GLFW_KEY_D) == GLFW_PRESS)
	{
		transform.position += glm::normalize(glm::cross(transform.front, transform.up)) * moveSpeed * deltaTime;
	}
	if (Input::GetKey(GLFW_KEY_E) == GLFW_PRESS)
	{
		transform.position += transform.up * moveSpeed * deltaTime;
	}
	if (Input::GetKey(GLFW_KEY_Q) == GLFW_PRESS)
	{
		transform.position -= transform.up * moveSpeed * deltaTime;
	}
}

void Camera::ProcessMouseInput(double x, double y, float deltaTime)
{
	if (Input::GetKey(GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
	{
		return;
	}

	static bool firstMouseInput = true;
	static float lastX = 0, lastY = 0;
	if (firstMouseInput)
	{
		firstMouseInput = false;
		lastX = x;
		lastY = y;
	}

	float xOffset = x - lastX;
	float yOffset = lastY - y;
	lastX = x;
	lastY = y;

	xOffset *= rotateSensity;
	yOffset *= rotateSensity;

	transform.rotate.yaw += xOffset * deltaTime;
	transform.rotate.pitch += yOffset * deltaTime;

	UpdateCameraVector();
}

void Camera::ProcessMouseWheelInput(double x, double y, float deltaTime)
{
	fov += -y * deltaTime;
	fov = glm::clamp(fov, 1.0f, 90.0f);
}

void Camera::UpdateCameraVector()
{
	transform.rotate.pitch = glm::clamp(transform.rotate.pitch, -89.0f, 89.0f);

	transform.front.x = cos(glm::radians(transform.rotate.yaw)) * cos(glm::radians(transform.rotate.pitch));
	transform.front.y = sin(glm::radians(transform.rotate.pitch));
	transform.front.z = sin(glm::radians(transform.rotate.yaw)) * cos(glm::radians(transform.rotate.pitch));
	transform.front = glm::normalize(transform.front);
}
