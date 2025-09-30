#include "WindowsWindow.h"

std::unordered_map<GLFWwindow*, WindowsWindow*> gWindowsWindowMap;

WindowsWindow::~WindowsWindow()
{
	destroyed = true;
	glfwTerminate();
}

void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void WindowsWindow::Update()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	ProcessInput(window);

	glfwSwapBuffers(window);
	glfwPollEvents();
}

bool WindowsWindow::IsExit()
{
	return destroyed || glfwWindowShouldClose(window);
}

void WindowsWindow::OnWindowInit()
{
	InitGLFW();
	InitGLAD();
	gWindowsWindowMap.insert(std::make_pair(GetWindow(), this));
}

void WindowsWindow::OnResolutionChange(unsigned int width, unsigned int height)
{
}

void OnSetFramebufferSize(GLFWwindow* window, int width, int height)
{
	auto it = gWindowsWindowMap.find(window);
	if (it != gWindowsWindowMap.end())
	{
		WindowsWindow* windowsWindow = it->second;
		windowsWindow->SetResolution(width, height);
	}
}

int WindowsWindow::InitGLFW()
{
	if (window != nullptr)
	{
		LogError("GLFW window is created.");
		return -1;
	}

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(windowData.width, windowData.height, windowData.title.c_str(), NULL, NULL);
	if (window == NULL)
	{
		LogError("Failed to create GLFW window.");
		glfwTerminate();

		return -1;
	}

	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, OnSetFramebufferSize);

	return 0;
}

int WindowsWindow::InitGLAD()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LogError("Failed to initialize GLAD.");
		return -1;
	}

	return 0;
}