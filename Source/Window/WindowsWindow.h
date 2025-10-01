#pragma once

#include "Core.h"
#include "Context.h"
#include "Window/Window.h"
#include "Loop/Loop.h"

#include <imgui.h>
#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

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