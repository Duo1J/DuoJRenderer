#pragma once

#include "DeltaTime.h"

class Loop
{
public:
	static void Init();

	static void Update();

	static float GetDeltaTime();

private:
	static DeltaTimeCalc deltaTimeCalc;
};