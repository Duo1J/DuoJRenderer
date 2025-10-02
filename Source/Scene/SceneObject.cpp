#include "SceneObject.h"

SceneObject::SceneObject(std::string _name)
{
	name = _name;
}

void SceneObject::Render()
{
	if (renderer != nullptr)
	{
		renderer->Render();
	}
}

void SceneObject::SetRenderer(Renderer* _renderer)
{
	_renderer->SetOwner(this);
	renderer = std::shared_ptr<Renderer>(_renderer);
}
