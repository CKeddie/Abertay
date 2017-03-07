#include "MeshRenderer.h"
#include "GameObject.h"
#include "graphics\material.h"

MeshRenderer::MeshRenderer(GameObject & gameObject, gef::MeshInstance * meshInstance) : 
	Component::Component(gameObject), 
	_meshInstance(meshInstance)
{
	_material = new Material();
}

MeshRenderer::MeshRenderer(GameObject & gameObject, gef::Model * model) : Component::Component(gameObject), _meshInstance(NULL)
{
	_meshInstance->set_mesh(model->mesh());
	_material = new Material(*model->material(0));
}

void MeshRenderer::Update(float deltaTime)
{
	
	_meshInstance->set_transform((_gameObject).GetTransformMatrix());
}

void MeshRenderer::Render(gef::Renderer3D * renderer)
{
	renderer->set_override_material(_material);
	renderer->DrawMesh(*_meshInstance);
}


MeshRenderer::~MeshRenderer()
{
}
