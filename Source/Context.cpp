#include "Context.h"

IWindow* Context::gWindow;
WindowsWindow* Context::gWindowsWindow;
Camera* Context::gMainCamera;
Scene* Context::gScene;

void Context::InitWindow()
{
	WindowData windowData;
	windowData.width = 1280;
	windowData.height = 720;
	windowData.title = "DuoJRenderer";

	gWindow = new WindowsWindow(windowData);
	gWindow->InitWindow();

	gWindowsWindow = static_cast<WindowsWindow*>(gWindow);
}

void Context::InitContext()
{
	stbi_set_flip_vertically_on_load(true);

	Transform cameraTransform;
	cameraTransform.position = glm::vec3(0, 0, 3);
	cameraTransform.front = glm::vec3(0, 0, -1);
	cameraTransform.up = glm::vec3(0, 1, 0);
	cameraTransform.rotate.yaw = -90;
	gMainCamera = new Camera(cameraTransform);
}

void Context::InitScene()
{
	gScene = new Scene();
	gScene->InitScene();
}

void Context::RenderScene()
{
	if (gScene != nullptr)
	{
		gScene->RenderScene();
	}
}

void Context::Exit()
{
	if (gWindow == nullptr)
	{
		return;
	}

	gWindow->Exit();
}

bool Context::IsExit()
{
	if (gWindow == nullptr)
	{
		return true;
	}

	return gWindow->IsExit();
}

void Context::UpdateWindow()
{
	if (gWindow == nullptr)
	{
		return;
	}

	gWindow->Update();
}

void Context::DestroyWindow()
{
	delete gWindow;
	gWindow = nullptr;
}

float Context::GetDeltaTime()
{
	return Loop::GetDeltaTime();
}