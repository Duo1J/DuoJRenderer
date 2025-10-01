#include "Input.h"

bool Input::GetKey(unsigned int key)
{
	return glfwGetKey(Context::gWindowsWindow->GetWindow(), key);
}
