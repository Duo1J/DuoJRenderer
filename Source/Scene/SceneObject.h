#pragma once

#include "Geometry/Transform.h"
#include "Render/Renderer.h"
#include <memory>

class Renderer;
class StaticMeshRenderer;

class SceneObject
{
public:
	std::string name;

	Transform transform;

public:
	SceneObject(std::string _name);

	virtual void Render();

	void SetRenderer(Renderer* _renderer);

private:
	std::shared_ptr<Renderer> renderer;
};