#include "Loop.h"
#include "Context.h"

DeltaTimeCalc Loop::deltaTimeCalc;

void Loop::Init()
{

}

void Loop::Update()
{
	float deltaTime = deltaTimeCalc.UpdateDeltaTime();

	Context::RenderScene();
}

float Loop::GetDeltaTime()
{
	return deltaTimeCalc.GetDeltaTime();
}