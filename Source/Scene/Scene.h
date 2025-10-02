#pragma once

#include "Core.h"
#include "Context.h"
#include "Geometry/Model.h"
#include "Resource/Resource.h"
#include "SceneObject.h"

class Model;
class SceneObject;

class Scene
{
public:
	Scene();

	void InitScene();
	void RenderScene();

	std::vector<SceneObject*> sceneObjects;
};