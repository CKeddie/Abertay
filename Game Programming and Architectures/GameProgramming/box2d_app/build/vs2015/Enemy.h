#pragma once
#include "Entity.h"
#include "maths\vector4.h"
#include <RigidBody.h>
#include <MeshRenderer.h>

class Enemy :
	public Entity
{
public:
	Enemy();
	void Update(float gametime);
	void CollisionCheck();
	void SetDirection(gef::Vector4 target);
	~Enemy();
protected:
	gef::Vector4 target_;
	bool enabled = true;
	b2Body* body;
};

