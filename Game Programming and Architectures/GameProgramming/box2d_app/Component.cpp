#include "Component.h"

Component::Component(GameObject& parent) :
	_gameObject(parent)
{
}

Component::~Component()
{

}

void Component::Update(float deltaTime)
{

}

void Component::Render(gef::Renderer3D* renderer)
{

}