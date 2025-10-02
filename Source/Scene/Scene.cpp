#include "Scene.h"
#include "Render/Renderer.h"
#include "Render/StaticMeshRenderer.h"
#include "Render/SkyboxRenderer.h"

Scene::Scene()
{
}

void Scene::InitScene()
{
	Resource::InitShader("Backpack")
		->Attach("F:/Scripts/Cpp/DuoJRenderer/Shader/BackpackVertex.glsl", ShaderType::VERTEX)
		.Attach("F:/Scripts/Cpp/DuoJRenderer/Shader/BackpackFragment.glsl", ShaderType::FRAGMENT)
		.Link();
	Resource::InitShader("Skybox")
		->Attach("F:/Scripts/Cpp/DuoJRenderer/Shader/SkyboxVertex.glsl", ShaderType::VERTEX)
		.Attach("F:/Scripts/Cpp/DuoJRenderer/Shader/SkyboxFragment.glsl", ShaderType::FRAGMENT)
		.Link();

	SceneObject* backpack = new SceneObject("backpack");
	StaticMeshRenderer* backpackRenderer = new StaticMeshRenderer;
	backpackRenderer->LoadModel("F:/Scripts/Cpp/DuoJRenderer/Asset/backpack/backpack.objx");
	backpackRenderer->SetShader("Backpack");
	backpack->SetRenderer(backpackRenderer);
	sceneObjects.push_back(backpack);

	std::vector<std::string> skyboxFaces
	{
		"F:/Scripts/Cpp/DuoJRenderer/Asset/skybox/T_Right.jpg",
		"F:/Scripts/Cpp/DuoJRenderer/Asset/skybox/T_Left.jpg",
		"F:/Scripts/Cpp/DuoJRenderer/Asset/skybox/T_Top.jpg",
		"F:/Scripts/Cpp/DuoJRenderer/Asset/skybox/T_Bottom.jpg",
		"F:/Scripts/Cpp/DuoJRenderer/Asset/skybox/T_Front.jpg",
		"F:/Scripts/Cpp/DuoJRenderer/Asset/skybox/T_Back.jpg"
	};

	SceneObject* skybox = new SceneObject("skybox");
	SkyboxRenderer* skyboxRenderer = new SkyboxRenderer;
	skyboxRenderer->LoadSkyboxCubemap(skyboxFaces);
	skyboxRenderer->SetShader("Skybox");
	skybox->SetRenderer(skyboxRenderer);
	sceneObjects.push_back(skybox);
}

void Scene::RenderScene()
{
	for (auto it = sceneObjects.begin(); it != sceneObjects.end(); ++it)
	{
		(*it)->Render();
	}
}
