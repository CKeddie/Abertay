#pragma once
#include "Component.h"
#include "Transform.h"
#include "graphics\renderer_3d.h"
#include "graphics\mesh_instance.h"
#include "graphics\mesh.h"

class MeshRenderer : public Component
{
public:
	MeshRenderer();
	~MeshRenderer();

	void Initialize(gef::Mesh * mesh, gef::Vector4 position, gef::Vector4 rotation, gef::Vector4 scale);
	void Update(gef::Matrix44 parentTransform);
	void Render(gef::Renderer3D* renderer);

	Transform* GetTransform() { return transform_; }

protected:
	Transform* transform_;
	gef::MeshInstance* mesh_instance_;
};

