#include "Input.h"
#include "Core.h"
#include <GLFW/glfw3.h>

bool Input::GetKey(unsigned int key)
{
	return glfwGetKey(gWindowsWindow->GetWindow(), key);
}
