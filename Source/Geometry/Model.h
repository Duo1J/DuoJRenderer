#pragma once

#include "Mesh.h"
#include "Shader/Shader.h"
#include "Texture/Texture.h"
#include "Resource/Resource.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>

class Model
{
public:
	Model(std::string modelPath);

	void Draw(const Shader& shader, int instanceCnt = 0);

	std::vector<Mesh> meshes;

private:

	std::string directory;

	void LoadModel(std::string modelPath);

	void ProcessNode(aiNode* node, const aiScene* scene);

	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType aiTexType, TextureType texType);
};

