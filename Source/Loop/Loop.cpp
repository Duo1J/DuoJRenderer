#include "Loop.h"
#include "Context.h"
#include "Render/RenderContext.h"
#include "Render/PostProcessPass.h"

DeltaTimeCalc Loop::deltaTimeCalc;

void Loop::Init()
{
	Render::InitRender();
	PostProcessPass::Init();
}

void Loop::Update()
{
	float deltaTime = deltaTimeCalc.UpdateDeltaTime();

	RenderContext::Prepare();

	PostProcessPass::BeginScene();

	if (Context::gScene != nullptr)
	{
		Context::gScene->RenderScene();
	}

	PostProcessPass::EndScene();

	PostProcessPass::Render();
}

float Loop::GetDeltaTime()
{
	return deltaTimeCalc.GetDeltaTime();
}