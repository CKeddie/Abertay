#pragma once

#include "graphics\renderer_3d.h"
#include "maths\transform.h"


class GameObject;

class Component
{
public:
	Component(GameObject& parent);
	virtual void Render(gef::Renderer3D* renderer);
	virtual void Update(float deltaTime);
	~Component();

	GameObject& _gameObject;
protected:
	//GameObject _gameObject;
};

