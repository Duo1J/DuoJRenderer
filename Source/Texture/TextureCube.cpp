#include "TextureCube.h"

TextureCube::TextureCube(std::vector<std::string> _faces)
{
	faces = _faces;
	LoadCubemap();
}

void TextureCube::LoadCubemap()
{
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	stbi_set_flip_vertically_on_load(false);

	int width, height, channel;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		const char* path = faces[i].c_str();
		unsigned char* data = stbi_load(path, &width, &height, &channel, 0);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_SRGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);

			Log("Load cubmap[" << GL_TEXTURE_CUBE_MAP_POSITIVE_X + i << "]: " << path << " success (with: " << width << " height: " << height << " channel: " << channel << " ID: " << textureID << ")");
		}
		else
		{
			LogError("Failed to load cubemap: " << path);
		}
	}

	stbi_set_flip_vertically_on_load(true);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}