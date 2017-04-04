#pragma once
#include "Entity.h"
class Asteroid :
	public Entity
{
public:
	Asteroid(GameObject & parent);
	void Update(float);

	~Asteroid();
};

