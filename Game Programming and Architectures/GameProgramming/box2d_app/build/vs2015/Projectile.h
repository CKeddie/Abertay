#pragma once
#include "Component.h"
class Projectile :
	public Component
{
public:
	Projectile(GameObject & parent);
	void Update(float gameTime);
	~Projectile();
};

