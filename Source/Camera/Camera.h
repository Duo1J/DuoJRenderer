#pragma once

#include "Core.h"
#include "Context.h"
#include "Geometry/Transform.h"
#include "Input/Input.h"

#include <glm.hpp>
#include <GLFW/glfw3.h>
#include <gtc/matrix_transform.hpp>

class Camera
{

public:
	Transform transform;

	float fov = 45;

	float moveSpeed = 2.5f;

	float rotateSensity = 0.05f;

	float near = 0.01f;

	float far = 100;

public:
	Camera();
	Camera(Transform& _transform);

	glm::mat4 GetViewMatrix();

	void ProcessKeyboardInput();

	void ProcessMouseInput(double x, double y);

	void ProcessMouseWheelInput(double x, double y);

	void UpdateCameraVector();
};

