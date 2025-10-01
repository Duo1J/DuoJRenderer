#include "Scene.h"

Scene::Scene()
{
}

void Scene::InitScene()
{
	model = Resource::LoadModel("F:/Scripts/Cpp/DuoJRenderer/Asset/backpack/backpack.objx");
	shader
		.Attach("F:/Scripts/Cpp/DuoJRenderer/Shader/BackpackVertex.glsl", ShaderType::VERTEX)
		.Attach("F:/Scripts/Cpp/DuoJRenderer/Shader/BackpackFragment.glsl", ShaderType::FRAGMENT)
		.Link();
}

glm::vec3 pointLightPositions[] = {
	glm::vec3(0.2f, 5, -3.54f),
	glm::vec3(10.7f, 0, -3),
	glm::vec3(-4.0f,  2.0f, -12.0f),
	glm::vec3(0.0f,  0.0f, -3.0f)
};

void Scene::RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	Camera* camera = Context::gMainCamera;
	IWindow* window = Context::gWindow;

	glm::mat4 view = camera->GetViewMatrix();
	glm::mat4 projection = glm::mat4(1);
	projection = glm::perspective(glm::radians(camera->fov), (float)window->GetWidth() / window->GetHeight(), camera->near, camera->far);

	shader.Use();
	shader.SetVec3("viewPos", camera->transform.position);

	shader.SetVec3("dirLight.ambient", glm::vec3(0.1f));
	shader.SetVec3("dirLight.diffuse", glm::vec3(0.9f));
	shader.SetVec3("dirLight.specular", glm::vec3(0.6f));
	shader.SetVec3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
	shader.SetFloat("material.shininess", 32.0f);

	for (int i = 0; i < 4; i++)
	{
		shader.SetVec3("pointLight[" + std::to_string(i) + "].ambient", glm::vec3(0.05f));
		shader.SetVec3("pointLight[" + std::to_string(i) + "].diffuse", glm::vec3(0.8f));
		shader.SetVec3("pointLight[" + std::to_string(i) + "].specular", glm::vec3(1.0f));
		shader.SetVec3("pointLight[" + std::to_string(i) + "].position", glm::vec3(pointLightPositions[i]));
		shader.SetFloat("pointLight[" + std::to_string(i) + "].constant", 1.0f);
		shader.SetFloat("pointLight[" + std::to_string(i) + "].diffuse", 0.09f);
		shader.SetFloat("pointLight[" + std::to_string(i) + "].quadratic", 0.032f);
	}

	glm::mat4 modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
	shader.SetMat4("model", modelMatrix);
	shader.SetMat4("view", view);
	shader.SetMat4("projection", projection);

	model->Draw(shader);
}
