#include "MeshRenderer.h"



MeshRenderer::MeshRenderer(GameObject* gameObject, MeshInstance meshInstance) : Component::Component(gameObject)
{
	_meshInstance = meshInstance;
}

void MeshRenderer::Update(float deltaTime)
{

}

void MeshRenderer::Render(gef::Renderer3D* renderer)
{
	renderer->DrawMesh(_meshInstance);	
}

MeshRenderer::~MeshRenderer()
{

}
