#include "PostProcessPass.h"
#include "Core.h"
#include "Context.h"
#include "Resource/Resource.h"
#include "BuiltinData.h"

#include "GLFW/glfw3.h"

float PostProcessPass::exposure = 1;
float PostProcessPass::gamma = 2.2f;

unsigned int PostProcessPass::sceneFBO;
unsigned int PostProcessPass::sceneRBO;
unsigned int PostProcessPass::sceneFrameBufferTex;
unsigned int PostProcessPass::screenQuadVAO;

std::shared_ptr<Shader> screenShader;

void PostProcessPass::Init()
{
	unsigned int screenQuadVBO;
	glGenVertexArrays(1, &screenQuadVAO);
	glGenBuffers(1, &screenQuadVBO);
	glBindVertexArray(screenQuadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, screenQuadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(screenQuadVertices), &screenQuadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	glGenFramebuffers(1, &sceneFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, sceneFBO);
	glGenTextures(1, &sceneFrameBufferTex);
	glBindTexture(GL_TEXTURE_2D, sceneFrameBufferTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, Context::gWindow->GetWidth(), Context::gWindow->GetHeight(), 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, sceneFrameBufferTex, 0);

	glGenRenderbuffers(1, &sceneRBO);
	glBindRenderbuffer(GL_RENDERBUFFER, sceneRBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Context::gWindow->GetWidth(), Context::gWindow->GetHeight());
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, sceneRBO);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		LogError("Postprocess scene FBO is not complete.");
		return;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	Resource::InitShader("Screen")
		->Attach("F:/Scripts/Cpp/DuoJRenderer/Shader/ScreenVertex.glsl", ShaderType::VERTEX)
		.Attach("F:/Scripts/Cpp/DuoJRenderer/Shader/ScreenFragment.glsl", ShaderType::FRAGMENT)
		.Link();
	screenShader = Resource::GetShader("Screen");
}

void PostProcessPass::BeginScene()
{
	glBindFramebuffer(GL_FRAMEBUFFER, sceneFBO);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void PostProcessPass::EndScene()
{
}

void PostProcessPass::Render()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	screenShader->Use();
	screenShader->SetInt("screenTexture", 0);
	screenShader->SetFloat("exposure", exposure);
	screenShader->SetFloat("gamma", gamma);
	glBindVertexArray(screenQuadVAO);
	glDisable(GL_DEPTH_TEST);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, sceneFrameBufferTex);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glEnable(GL_DEPTH_TEST);
}

void PostProcessPass::OnResolutionChange(unsigned int width, unsigned int height)
{
	glBindTexture(GL_TEXTURE_2D, sceneFrameBufferTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindRenderbuffer(GL_RENDERBUFFER, sceneRBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
}
