#pragma once
#include "Entity.h"

class Projectile :
	public Entity
{
public:
	Projectile();
	Projectile(gef::Vector4 spawn);
	void Update(float gameTime);
	void CollisionCheck();
	void Reset();
	~Projectile();
	void SetParentTransform(Transform* parent) { parent_transform = parent; }
	void Fire() { is_fired = true; }
	void Reload() { is_fired = false; }
private:
	bool is_fired = false;
	Transform* parent_transform;
	float timer_ = 0, time_limit_ = 3;
};

