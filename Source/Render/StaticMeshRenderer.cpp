#include "StaticMeshRenderer.h"
#include "RenderContext.h"

#include "glm.hpp"
#include <gtc/matrix_transform.hpp>

#include "assert.h"

void StaticMeshRenderer::Render()
{
	assert(model);

	Renderer::Render();

	shader->SetVec3("dirLight.ambient", glm::vec3(0.1f));
	shader->SetVec3("dirLight.diffuse", glm::vec3(0.9f));
	shader->SetVec3("dirLight.specular", glm::vec3(0.6f));
	shader->SetVec3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
	shader->SetFloat("material.shininess", 32.0f);

	shader->SetInt("pointLightNum", 0);

	model->Draw(*shader);
}

void StaticMeshRenderer::LoadModel(std::string modelPath)
{
	model = Resource::LoadModel(modelPath);
}
