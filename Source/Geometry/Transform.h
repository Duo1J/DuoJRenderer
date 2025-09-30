#pragma once

#include <glm.hpp>
#include "EulerAngle.h"

struct Transform
{
	glm::vec3 position = glm::vec3(0, 0, 0);

	glm::vec3 front = glm::vec3(0, 0, 0);

	glm::vec3 up = glm::vec3(0, 0, 0);

	glm::vec3 right = glm::vec3(0, 0, 0);

	EulerAngle rotate;
};