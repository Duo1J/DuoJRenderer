#pragma once

#include <string>

struct WindowData
{
public:
	std::string title;
	unsigned int width;
	unsigned int height;
};

template<typename T>
class Window
{
public:
	Window(const WindowData& _windowData)
	{
		windowData = _windowData;
	}

	T*& InitWindow()
	{
		OnWindowInit();
		return GetWindow();
	}

	virtual T*& GetWindow() { return window; }

	unsigned int GetWidth() { return windowData.width; }
	unsigned int GetHeight() { return windowData.height; }

	void SetResolution(unsigned int width, unsigned int height)
	{
		windowData.width = width;
		windowData.height = height;
		OnResolutionChange(width, height);
	}

	virtual void Update() = 0;
	virtual bool IsExit() = 0;

protected:
	T* window = nullptr;

	WindowData windowData;

	bool destroyed = false;

protected:
	virtual void OnWindowInit() = 0;
	virtual void OnResolutionChange(unsigned int width, unsigned int height) = 0;
};