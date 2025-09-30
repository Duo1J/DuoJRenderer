#include "Core/Core.h"
#include <iostream>

#include <GLFW/glfw3.h>

#include "Core/Window/WindowsWindow.h"

int main()
{
	WindowData windowData;
	windowData.width = 1280;
	windowData.height = 720;
	windowData.title = "DuoJRenderer";
	WindowsWindow* windowsWindow = new WindowsWindow(windowData);
	windowsWindow->InitWindow();
	GLFWwindow* window = windowsWindow->GetWindow();

	while (!windowsWindow->IsExit())
	{
		windowsWindow->Update();
	}

	delete windowsWindow;

	return 0;
}