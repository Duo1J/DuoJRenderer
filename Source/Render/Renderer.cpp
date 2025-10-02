#include "Renderer.h"
#include <assert.h>

void Renderer::SetShader(std::string shaderName)
{
	shader = Resource::GetShader(shaderName);
}

void Renderer::SetOwner(SceneObject* _owner)
{
	owner = _owner;
}

void Renderer::Render()
{
	assert(shader && owner);

	shader->Use();

	glm::mat4 modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, owner->transform.position);
	//modelMatrix = glm::rotate(modelMatrix, owner->transform.rotate.pitch, owner->transform.right);
	//modelMatrix = glm::rotate(modelMatrix, owner->transform.rotate.yaw, owner->transform.up);
	//modelMatrix = glm::rotate(modelMatrix, owner->transform.rotate.roll, owner->transform.front);
	modelMatrix = glm::scale(modelMatrix, owner->transform.scale);
	shader->SetMat4("model", modelMatrix);
	shader->SetMat4("view", RenderContext::view);
	shader->SetMat4("projection", RenderContext::projection);
	shader->SetVec3("viewPos", RenderContext::viewPos);
}