#include "Asteroid.h"

#include "GameObject.h"
#include "MeshRenderer.h"

Asteroid::Asteroid() : Entity()
{
}

void Asteroid::Update(float gameTime)
{
	Entity::Update(gameTime);
	CollisionCheck();

	gef::Vector4 v = spawn_point_;
	v.Normalise();
	float r = 0.25f;// static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	rigid_body_->SetAngularVelocity(0.0f);
	//r = r <= 0 ? r + 0.1f : r;
	rigid_body_->SetVelocity(-v.x() * r, -v.y() * r);
}

void Asteroid::CollisionCheck()
{
	Entity::CollisionCheck();

	switch (rigid_body_->GetCurrentColliding())
	{
	case PLAYER:
	{
		current_health_--;
		break;
	}
	case ENEMY:
	{
		current_health_--;
		break;
	}
	case PROJECTILE:
	{
		current_health_--;
		break;
	}
	case NONE:
		break;
	}
}



Asteroid::~Asteroid()
{
}
