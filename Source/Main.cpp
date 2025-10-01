#include "Core.h"
#include "Context.h"
#include "Render/Renderer.h"

int main()
{
	Context::InitWindow();
	Context::InitContext();
	Context::InitScene();

	Renderer::InitRenderer();

	Loop::Init();

	while (!Context::IsExit())
	{
		Context::UpdateWindow();
	}

	Context::DestroyWindow();

	return 0;
}