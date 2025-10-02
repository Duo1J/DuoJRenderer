#include "Resource.h"

std::unordered_map<std::string, std::shared_ptr<Texture>> Resource::texturesLoaded;
std::unordered_map<std::string, std::shared_ptr<Model>> Resource::modelsLoaded;
std::unordered_map<std::string, std::shared_ptr<Shader>> Resource::shadersLoaded;

std::shared_ptr<Texture> Resource::LoadTexture(std::string texturePath, TextureType texType)
{
	auto it = texturesLoaded.find(texturePath);
	if (it != texturesLoaded.end())
	{
		return it->second;
	}

	Texture* texture = new Texture(texturePath.c_str(), texType);
	std::shared_ptr<Texture> ptr(texture);
	texturesLoaded.insert(std::make_pair(texturePath, ptr));
	return ptr;
}

std::shared_ptr<Model> Resource::LoadModel(std::string modelPath)
{
	auto it = modelsLoaded.find(modelPath);
	if (it != modelsLoaded.end())
	{
		return it->second;
	}

	Model* model = new Model(modelPath);
	std::shared_ptr<Model> ptr(model);
	modelsLoaded.insert(std::make_pair(modelPath, ptr));
	return ptr;
}

std::shared_ptr<Shader> Resource::InitShader(std::string shaderName)
{
	auto it = shadersLoaded.find(shaderName);
	if (it != shadersLoaded.end())
	{
		return it->second;
	}

	Shader* shader = new Shader();
	std::shared_ptr<Shader> shaderPtr(shader);
	shadersLoaded.insert(std::make_pair(shaderName, shaderPtr));
	Log("Init Shader: " << shaderName);
	return shaderPtr;
}

std::shared_ptr<Shader> Resource::GetShader(std::string shaderName)
{
	auto it = shadersLoaded.find(shaderName);
	if (it != shadersLoaded.end())
	{
		return it->second;
	}

	LogError("Shader is not init: " << shaderName);
	return nullptr;
}