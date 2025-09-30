#pragma once

#include "Core.h"
#include "Window/Window.h"
#include "Window/WindowsWindow.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

static IWindow* gWindow = nullptr;
static WindowsWindow* gWindowsWindow = nullptr;

void InitWindow()
{
	WindowData windowData;
	windowData.width = 1280;
	windowData.height = 720;
	windowData.title = "DuoJRenderer";

	gWindow = new WindowsWindow(windowData);
	gWindow->InitWindow();

	gWindowsWindow = static_cast<WindowsWindow*>(gWindow);
}

void Exit()
{
	if (gWindow == nullptr)
	{
		return;
	}

	gWindow->Exit();
}

bool IsExit()
{
	if (gWindow == nullptr)
	{
		return true;
	}

	return gWindow->IsExit();
}

void UpdateWindow()
{
	if (gWindow == nullptr)
	{
		return;
	}

	gWindow->Update();
}

void DestroyWindow()
{
	delete gWindow;
	gWindow = nullptr;
}