#pragma once

#include <string>

struct WindowData
{
public:
	std::string title = "";
	unsigned int width = 0;
	unsigned int height = 0;
};

class IWindow
{
public:
	unsigned int GetWidth() { return windowData.width; }
	unsigned int GetHeight() { return windowData.height; }

	virtual void Update() = 0;

	virtual void Exit() = 0;
	virtual bool IsExit() = 0;

	void InitWindow()
	{
		OnWindowInit();
	}

	void SetResolution(unsigned int width, unsigned int height)
	{
		windowData.width = width;
		windowData.height = height;
		OnResolutionChange(width, height);
	}

protected:
	WindowData windowData;

	bool destroyed = false;

protected:
	virtual void OnWindowInit() = 0;
	virtual void OnResolutionChange(unsigned int width, unsigned int height) = 0;
};

template<typename T>
class Window : public IWindow
{
public:
	Window(const WindowData& _windowData)
	{
		windowData = _windowData;
	}

	virtual T*& GetWindow() { return window; }

protected:
	T* window = nullptr;
};