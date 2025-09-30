#pragma once

#include "Core/Core.h"
#include <unordered_map>

#include <GLFW/glfw3.h>

#include "Core/Window/Window.h"

class WindowsWindow : public Window<GLFWwindow>
{
public:
	WindowsWindow(const WindowData& _windowData) : Window<GLFWwindow>(_windowData) {}
	~WindowsWindow();

	void Update() override;
	bool IsExit() override;

protected:
	void OnWindowInit() override;
	void OnResolutionChange(unsigned int width, unsigned int height) override;

private:
	int InitGLFW();
	int InitGLAD();
};