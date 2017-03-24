#include "Entity.h"


Entity::Entity(GameObject & parent) : Component::Component(parent)
{
}

Entity::~Entity()
{
}

void Entity::Reset()
{
}

void Entity::Update(float deltaTime)
{
}

void Entity::Render(gef::Renderer3D * renderer)
{
}
