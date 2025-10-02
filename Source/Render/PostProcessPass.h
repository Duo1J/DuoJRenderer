#pragma once

class PostProcessPass
{
public:
	static void Init();

	static void BeginScene();

	static void EndScene();

	static void Render();

	static void OnResolutionChange(unsigned int width, unsigned int height);

public:
	static float exposure;
	static float gamma;

private:
	static unsigned int sceneFBO;
	static unsigned int sceneRBO;
	static unsigned int sceneFrameBufferTex;
	static unsigned int screenQuadVAO;
};