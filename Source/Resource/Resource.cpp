#include "Resource.h"

std::unordered_map<std::string, std::shared_ptr<Texture>> Resource::texturesLoaded;
std::unordered_map<std::string, std::shared_ptr<Model>> Resource::modelsLoaded;

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
