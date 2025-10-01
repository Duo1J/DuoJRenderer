#pragma once

#include <vector>

#include "Core.h"
#include "Vertex.h"
#include "Texture/Texture.h"
#include "Shader/Shader.h"

#include <glad/glad.h>
#include <assert.h>

class Mesh
{
public:
	std::vector<Vertex> vertices;

	std::vector<unsigned int> indices;

	std::vector<Texture> textures;

	Mesh(std::vector<Vertex> _vertices, std::vector<unsigned int> _indices, std::vector<Texture> _textures);

	void Draw(const Shader& shader, int instanceCnt = 0);

	void BindVAO();

	void UnBindVAO();

private:
	unsigned int VAO, VBO, EBO;

	void CreateBuffer();
};

