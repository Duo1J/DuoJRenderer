#pragma once

#include "Window/Window.h"
#include "Window/WindowsWindow.h"
#include "Camera/Camera.h"
#include "Scene/Scene.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

class Context;
class IWindow;
class WindowsWindow;
class Camera;
class Scene;

class Context
{
public:
	static IWindow* gWindow;
	static WindowsWindow* gWindowsWindow;
	static Camera* gMainCamera;
	static Scene* gScene;

public:
	static void InitWindow();

	static void InitContext();

	static void InitScene();

	static void RenderScene();

	static void Exit();

	static bool IsExit();

	static void UpdateWindow();

	static void DestroyWindow();

	static float GetDeltaTime();
};