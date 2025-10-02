#pragma once

#include "Renderer.h"
#include "Texture/TextureCube.h"

class TextureCube;

class SkyboxRenderer : public Renderer
{
public:
	SkyboxRenderer();
	void Render() override;
	void LoadSkyboxCubemap(std::vector<std::string> _faces);

private:
	unsigned int skyboxVAO;
	std::shared_ptr<TextureCube> skyboxCubemap;
};