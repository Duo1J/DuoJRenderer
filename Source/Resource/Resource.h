#pragma once

#include "Core.h"
#include "Context.h"
#include "Texture/Texture.h"
#include "Geometry/Model.h"

#include <string>
#include <unordered_map>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Texture;
class Model;

class Resource
{
public:
	static std::shared_ptr<Texture> LoadTexture(std::string texturePath, TextureType texType);

	static std::shared_ptr<Model> LoadModel(std::string modelPath);

	static std::shared_ptr<Shader> InitShader(std::string shaderName);

	static std::shared_ptr<Shader> GetShader(std::string shaderName);

private:
	static std::unordered_map<std::string, std::shared_ptr<Texture>> texturesLoaded;

	static std::unordered_map<std::string, std::shared_ptr<Model>> modelsLoaded;

	static std::unordered_map<std::string, std::shared_ptr<Shader>> shadersLoaded;
};