#pragma once

#include "Core.h"

#include <GLFW/glfw3.h>
#include "stb_image.h"

#include <iostream>
#include <vector>

class TextureCube
{
public:
	unsigned int textureID = 0;

public:
	explicit TextureCube(std::vector<std::string> _faces);

private:
	std::vector<std::string> faces;

	void LoadCubemap();
};

