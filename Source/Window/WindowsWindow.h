#pragma once

#include "Core.h"
#include "Window/Window.h"

#include <unordered_map>

#include <GLFW/glfw3.h>

class WindowsWindow : public Window<GLFWwindow>
{
public:
	WindowsWindow(const WindowData& _windowData) : Window<GLFWwindow>(_windowData) {}
	~WindowsWindow();

	void Update() override;

	void Exit() override;
	bool IsExit() override;

protected:
	void OnWindowInit() override;
	void OnResolutionChange(unsigned int width, unsigned int height) override;

private:
	int InitGLFW();
	int InitGLAD();
	int InitImGUI();
};