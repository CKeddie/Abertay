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
	Enemy(gef::Vector4 spawn);
	void Update(float gametime);
	void CollisionCheck();
	void SetDirection(gef::Vector4 target);
	~Enemy();
protected:
	gef::Vector4 target_;
	bool enabled = true;
	float angle = -90;
	float new_angle = -45, left_angle = -135, right_angle = -45;
};

