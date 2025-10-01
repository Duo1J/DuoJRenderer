#include "DeltaTime.h"

float DeltaTimeCalc::deltaTime;
float DeltaTimeCalc::lastFrameTime;

float DeltaTimeCalc::UpdateDeltaTime()
{
	float currentFrameTime = glfwGetTime();
	deltaTime = currentFrameTime - lastFrameTime;
	lastFrameTime = currentFrameTime;
	return GetDeltaTime();
}

float DeltaTimeCalc::GetDeltaTime()
{
	return deltaTime;
}