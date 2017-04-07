#pragma once
#include "Entity.h"

class Projectile :
	public Entity
{
public:
	Projectile();
	void Update(float gameTime);
	void CollisionCheck();
	~Projectile();
	void SetParentTransform(Transform* parent) { parent_transform = parent; }
	void Fire() { is_fired = true; }
private:
	bool is_fired = false;
	Transform* parent_transform;
};

