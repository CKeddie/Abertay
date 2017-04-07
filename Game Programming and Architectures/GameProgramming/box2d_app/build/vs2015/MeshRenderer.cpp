#include "MeshRenderer.h"


MeshRenderer::MeshRenderer() 
	: mesh_instance_(NULL)
	, transform_(NULL)
{
}

MeshRenderer::~MeshRenderer()
{
	delete mesh_instance_;
	mesh_instance_ = NULL;

	delete transform_;
	transform_ = NULL;
}

void MeshRenderer::Initialize(gef::Mesh* mesh, gef::Vector4 position, gef::Vector4 rotation, gef::Vector4 scale)
{
	mesh_instance_ = new gef::MeshInstance();
	mesh_instance_->set_mesh(mesh);
	transform_ = new Transform();
	transform_->Initialize(position, rotation, scale);
	transform_->UpdateMatrices();
	mesh_instance_->set_transform(transform_->GetTransform());
}

void MeshRenderer::Update(gef::Matrix44 parentTransform)
{
	if (transform_)
		transform_->UpdateMatrices();
	mesh_instance_->set_transform(transform_->GetTransform() * parentTransform);
}

void MeshRenderer::Render(gef::Renderer3D * renderer)
{
	renderer->DrawMesh(*mesh_instance_);
}
