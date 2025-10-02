#include "RenderContext.h"

glm::mat4 RenderContext::view;

glm::mat4 RenderContext::projection;

glm::vec3 RenderContext::viewPos;

void RenderContext::Prepare()
{
	Camera* camera = Context::gMainCamera;
	IWindow* window = Context::gWindow;

	view = camera->GetViewMatrix();
	projection = glm::mat4(1);
	projection = glm::perspective(glm::radians(camera->fov), (float)window->GetWidth() / window->GetHeight(), camera->near, camera->far);
	viewPos = camera->transform.position;
}
