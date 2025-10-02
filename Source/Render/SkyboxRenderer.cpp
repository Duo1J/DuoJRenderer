#include "SkyboxRenderer.h"
#include "BuiltinData.h"

SkyboxRenderer::SkyboxRenderer()
{
	unsigned int skyboxVBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}

void SkyboxRenderer::Render()
{
	assert(shader && owner && skyboxCubemap);

	glDepthFunc(GL_LEQUAL);

	shader->Use();
	shader->SetMat4("projection", RenderContext::projection);
	shader->SetMat4("view", glm::mat4(glm::mat3(RenderContext::view)));
	shader->SetVec3("viewPos", RenderContext::viewPos);
	shader->SetInt("skybox", 0);
	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxCubemap->textureID);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	glDepthFunc(GL_LESS);
}

void SkyboxRenderer::LoadSkyboxCubemap(std::vector<std::string> _faces)
{
	TextureCube* textureCube = new TextureCube(_faces);
	skyboxCubemap = std::shared_ptr<TextureCube>(textureCube);
}
