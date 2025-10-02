#include "WindowsWindow.h"
#include <unordered_map>

#include "Render/PostProcessPass.h"

#define NEW_FRAME ImGui_ImplOpenGL3_NewFrame(); \
				  ImGui_ImplGlfw_NewFrame(); \
				  ImGui::NewFrame();

static std::unordered_map<GLFWwindow*, WindowsWindow*> gWindowsWindowMap;

WindowsWindow::~WindowsWindow()
{
	Exit();
}

void OnKeyboardInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_ALT))
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	else
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	if (Context::gMainCamera != nullptr)
	{
		Context::gMainCamera->ProcessKeyboardInput();
	}
}

void UpdateImGUI()
{
	ImGui::Begin("Hierarchy");

	for (auto it : Context::gScene->sceneObjects)
	{
		ImGui::Text(it->name.c_str());
	}

	ImGui::End();

	ImGui::Begin("Option");

	ImGui::SliderFloat("exposure", &PostProcessPass::exposure, 0.1f, 2.0f);
	ImGui::SliderFloat("gamma", &PostProcessPass::gamma, 1.4f, 3.2f);

	ImGui::End();
}

void WindowsWindow::Update()
{
	OnKeyboardInput(window);

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
	glViewport(0, 0, width, height);

	if (Context::gMainCamera != nullptr)
	{
		Context::gMainCamera->UpdateCameraVector();
	}

	PostProcessPass::OnResolutionChange(width, height);
}

void OnSetFramebufferSize(GLFWwindow* window, int width, int height)
{
	auto it = gWindowsWindowMap.find(window);
	if (it != gWindowsWindowMap.end())
	{
		WindowsWindow* window = it->second;
		window->SetResolution(width, height);
	}
}

void OnMouseInput(GLFWwindow* window, double x, double y)
{
	if (Context::gMainCamera != nullptr)
	{
		Context::gMainCamera->ProcessMouseInput(x, y);
	}
}

void OnMouseWheelInput(GLFWwindow* window, double x, double y)
{
	if (Context::gMainCamera != nullptr)
	{
		Context::gMainCamera->ProcessMouseWheelInput(x, y);
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
	glfwSetCursorPosCallback(window, OnMouseInput);
	glfwSetScrollCallback(window, OnMouseWheelInput);

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
