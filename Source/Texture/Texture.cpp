#include "Texture.h"
#include <assert.h>

Texture::Texture(const char* _texturePath, TextureType _textureType, unsigned int wrap)
{
	texturePath = _texturePath;
	textureType = _textureType;

	bool gammaCorrection = false;
	if (textureType == TextureType::DIFFUSE)
	{
		gammaCorrection = true;
	}

	glGenTextures(1, &textureID);

	unsigned char* textureData = stbi_load(_texturePath, &width, &height, &channel, 0);
	if (textureData)
	{
		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int internalFormat, dataFormat;
		if (channel == 4)
		{
			internalFormat = gammaCorrection ? GL_SRGB_ALPHA : GL_RGBA;
			dataFormat = GL_RGBA;
		}
		else if (channel == 3)
		{
			internalFormat = gammaCorrection ? GL_SRGB : GL_RGB;
			dataFormat = GL_RGB;
		}
		else if (channel == 2)
		{
			internalFormat = dataFormat = GL_RG;
		}
		else
		{
			internalFormat = dataFormat = GL_RED;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, textureData);

		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(textureData);
		Log("Load texture: " << texturePath << " success (width: " << width << " height: " << height << " channel: " << channel << " ID: " << textureID << ")");
	}
	else
	{
		LogError("Failed to load texture: ", texturePath);
	}
}

std::string Texture::GetTextureTypeName()
{
	if (textureType == TextureType::DIFFUSE)
	{
		return "tex_diffuse";
	}
	else if (textureType == TextureType::COMMON)
	{
		return "tex_diffuse";
	}
	else if (textureType == TextureType::SPECULAR)
	{
		return "tex_specular";
	}
	else if (textureType == TextureType::NORMAL)
	{
		return "tex_normal";
	}
	else
	{
		LogError("Undefined texture type: ", textureType);
		assert(false);
		return "";
	}
}
