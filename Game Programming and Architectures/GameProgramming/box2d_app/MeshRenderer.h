#pragma once
#include "Component.h"

#include "graphics\mesh.h"
#include "graphics\mesh_instance.h"
#include "graphics\model.h"
#include "graphics\material.h"
#include "graphics\material.h"
#include "maths\math_utils.h"

class GameObject;

class MeshRenderer :
	public Component
{
public:
	MeshRenderer(GameObject& gameObject, gef::Mesh* mesh, gef::Material* material, gef::Vector4 rotation);
	MeshRenderer(GameObject& gameObject, gef::Mesh* mesh, gef::Material* material, gef::Vector4 rotation, gef::Vector4 position);
	void TiltZ(float radians);
	void TiltY(float radians);
	void TiltX(float radians);
	//MeshRenderer(GameObject& gameObject, gef::Model* model);
	void Update(float deltaTime);
	void Render(gef::Renderer3D* renderer);
	bool IsDrawable() { return is_drawable_; }
	void SetDrawable(bool value) { is_drawable_ = value; }
	~MeshRenderer();

	void SetMaterial(gef::Material* material) { _material = material; }
	gef::Material* GetMaterial() { return _material; }
protected:
	class gef::MeshInstance* _meshInstance;
	class gef::Material* _material;
	gef::Matrix44 transform_, pitch_, yaw_, roll_, translation_;
	bool is_drawable_ = true;
};

