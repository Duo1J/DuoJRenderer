#pragma once

#include "Core.h"
#include "Context.h"
#include "Geometry/Model.h"
#include "Resource/Resource.h"

class Model;

class Scene
{
public:
	Scene();

	void InitScene();
	void RenderScene();

	std::shared_ptr<Model> model;
	Shader shader;
};