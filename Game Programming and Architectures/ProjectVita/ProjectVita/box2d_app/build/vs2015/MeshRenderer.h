#pragma once
#include "Component.h"
#include "graphics\mesh_instance.h"
class MeshRenderer :
	public Component
{
public:
	MeshRenderer(GameObject* gameObjecy, MeshInstance meshInstance);
	void Update(float deltaTime);
	void Render(gef::Renderer3D* renderer);
	~MeshRenderer();
protected:
	gef::MeshInstance _meshInstance;
};

