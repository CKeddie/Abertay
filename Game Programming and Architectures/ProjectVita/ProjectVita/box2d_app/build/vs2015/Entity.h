#pragma once
#include "Component.h"

class Entity :
	public Component
{
public:
	Entity(GameObject & parent);
	void Update(float deltaTime);
	void Render(gef::Renderer3D* renderer);
	~Entity();
protected:
};

