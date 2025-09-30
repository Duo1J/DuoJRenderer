#pragma once

#include <glm.hpp>

#include "Geometry/Transform.h"

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

	void ProcessKeyboardInput(float deltaTime);

	void ProcessMouseInput(double x, double y, float deltaTime);

	void ProcessMouseWheelInput(double x, double y, float deltaTime);

	void UpdateCameraVector();
};

