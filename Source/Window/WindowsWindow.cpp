#include "WindowsWindow.h"
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include "Loop/Loop.h"

#define NEW_FRAME ImGui_ImplOpenGL3_NewFrame(); \
				  ImGui_ImplGlfw_NewFrame(); \
				  ImGui::NewFrame();

std::unordered_map<GLFWwindow*, WindowsWindow*> gWindowsWindowMap;

WindowsWindow::~WindowsWindow()
{
	Exit();
}

void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void UpdateImGUI()
{

}

void WindowsWindow::Update()
{
	ProcessInput(window);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	NEW_FRAME;

	Loop::Update();

	UpdateImGUI();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(window);
	glfwPollEvents();
}

void WindowsWindow::Exit()
{
	if (destroyed)
	{
		return;
	}
	destroyed = true;

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
}

bool WindowsWindow::IsExit()
{
	return destroyed || glfwWindowShouldClose(window);
}

void WindowsWindow::OnWindowInit()
{
	InitGLFW();
	InitGLAD();
	InitImGUI();

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

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

int WindowsWindow::InitImGUI()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(GetWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 460");

	return 0;
}
