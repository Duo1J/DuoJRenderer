#pragma once

#include "Renderer.h"
#include "Geometry/Model.h"

class Model;

class StaticMeshRenderer : public Renderer
{
public:
	void Render() override;
	void LoadModel(std::string modelPath);

private:
	std::shared_ptr<Model> model;
};