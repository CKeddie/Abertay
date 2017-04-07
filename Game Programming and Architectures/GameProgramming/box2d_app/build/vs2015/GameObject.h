#pragma once

#include "graphics\renderer_3d.h"

#include <Transform.h>

class GameObject
{
public:
	GameObject();
	~GameObject();

	virtual void Update(float);
	virtual void Render(gef::Renderer3D*) = 0;

	Transform* GetTransform() { return tranform_; }
protected:
	Transform* tranform_;
};

