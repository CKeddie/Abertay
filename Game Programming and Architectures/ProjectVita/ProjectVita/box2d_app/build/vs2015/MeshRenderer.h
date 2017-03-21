#pragma once
#include "Component.h"
#include "graphics\mesh_instance.h"
#include "graphics\model.h"
#include "graphics\material.h"

class GameObject;

class MeshRenderer :
	public Component
{
public:
	MeshRenderer(GameObject& gameObject, gef::MeshInstance* meshInstance);
	//MeshRenderer(GameObject& gameObject, gef::Model* model);
	void Update(float deltaTime);
	void Render(gef::Renderer3D* renderer);
	~MeshRenderer();

	void SetMaterial(gef::Material material) { _material = material; }
	gef::Material* GetMaterial() { return &_material; }
protected:
	gef::MeshInstance& _meshInstance;
	gef::Material _material;
};

