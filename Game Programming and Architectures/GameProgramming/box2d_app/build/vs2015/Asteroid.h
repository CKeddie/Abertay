#pragma once
#include "Entity.h"
class Asteroid :
	public Entity
{
public:
	Asteroid();
	void Update(float);

	void CollisionCheck();

	~Asteroid();
};

