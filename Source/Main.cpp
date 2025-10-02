#include "Core.h"
#include "Context.h"

int main()
{
	Context::InitWindow();
	Context::InitContext();

	while (!Context::IsExit())
	{
		Context::UpdateWindow();
	}

	Context::DestroyWindow();

	return 0;
}