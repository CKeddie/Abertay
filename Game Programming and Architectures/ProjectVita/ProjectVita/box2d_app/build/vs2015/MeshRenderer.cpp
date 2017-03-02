#include "MeshRenderer.h"
#include "GameObject.h"

MeshRenderer::MeshRenderer(GameObject & gameObject, gef::MeshInstance * meshInstance) : 
	Component::Component(gameObject), 
	_meshInstance(meshInstance)
{
}

void MeshRenderer::Update(float deltaTime)
{
	_meshInstance->set_transform(_gameObject.GetTransformMatrix());
}

void MeshRenderer::Render(gef::Renderer3D * renderer)
{
	renderer->DrawMesh(*_meshInstance);
}


MeshRenderer::~MeshRenderer()
{
}
