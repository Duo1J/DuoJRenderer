#pragma once

#include "RenderContext.h"
#include "Shader/Shader.h"
#include "Scene/SceneObject.h"
#include <string>

class SceneObject;

class Renderer
{
public:
	void SetShader(std::string shaderName);
	void SetOwner(SceneObject* _owner);

	virtual void Render();

protected:
	SceneObject* owner;

	std::shared_ptr<Shader> shader;
};