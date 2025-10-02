#pragma once

#include "Context.h"
#include "glm.hpp"

class RenderContext
{
public:
	static void Prepare();

	static glm::mat4 view;

	static glm::mat4 projection;

	static glm::vec3 viewPos;
};