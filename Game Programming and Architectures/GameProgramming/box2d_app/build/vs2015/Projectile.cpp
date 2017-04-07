#include "Projectile.h"


Projectile::Projectile() 
	: Entity()
{
	
}

void Projectile::Update(float gameTime)
{
	Entity::Update(gameTime);

	if (!is_fired)
	{
		rigid_body_->SetPosition(parent_transform->GetPosition());
	}
	else
	{
		rigid_body_->GetBody()->ApplyForceToCenter(b2Vec2(0, 1), true);
	}
}

void Projectile::CollisionCheck()
{
	Entity::CollisionCheck();

	switch (rigid_body_->GetCurrentColliding())
	{

	case ENEMY:
	{
		current_health_--;
		break;
	}
	case ASTEROID:
	{
		current_health_--;
		break;
	}
	case NONE:
		break;
	}
}


Projectile::~Projectile()
{
}
