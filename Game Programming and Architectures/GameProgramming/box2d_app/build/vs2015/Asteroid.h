#pragma once
#include "Entity.h"
class Asteroid :
	public Entity
{
public:
	Asteroid();
	Asteroid(gef::Vector4 spawn);
	void Update(float);

	void CollisionCheck();

	~Asteroid();
};

