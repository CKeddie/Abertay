#pragma once

#include "graphics\renderer_3d.h"
#include "maths\transform.h"
#include "GameObject.h"


class Component
{
public:
	Component(GameObject * parent);
	~Component();

	virtual void Render(gef::Renderer3D* renderer);
	virtual void Update(float deltaTime);

	GameObject* GetGameObject() { return _gameObject; }
protected:
	GameObject* _gameObject;
};

