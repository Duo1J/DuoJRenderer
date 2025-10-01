#pragma once

#include <GLFW/glfw3.h>

class DeltaTimeCalc
{
public:
	static float UpdateDeltaTime();

	static float GetDeltaTime();

private:
	static float deltaTime;
	static float lastFrameTime;
};