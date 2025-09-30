#pragma once

#include <string>

#include <Core.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

enum class TextureType
{
	COMMON,
	DIFFUSE,
	SPECULAR,
	NORMAL,
};

class Texture
{
public:
	int width = 0;

	int height = 0;

	int channel = 0;

	TextureType textureType;

	std::string texturePath;

	unsigned int textureID = 0;

public:
	explicit Texture(const char* _texturePath, TextureType _textureType, unsigned int wrap = GL_REPEAT);

	std::string GetTextureTypeName();
};

