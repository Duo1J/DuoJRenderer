#include "Core.h"

int main()
{
	InitWindow();

	while (!IsExit())
	{
		UpdateWindow();
	}

	DestroyWindow();

	return 0;
}