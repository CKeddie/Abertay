#include "Projectile.h"


Projectile::Projectile()
	: Entity()
{

}

Projectile::Projectile(gef::Vector4 spawn)
	: Entity(spawn)
{

}

void Projectile::Update(float gameTime)
{
	Entity::Update(gameTime);
	if (!is_fired)
	{
		spawn_point_ = parent_transform->GetPosition();
		rigid_body_->SetPosition(parent_transform->GetPosition());
	}
	else
	{
		rigid_body_->SetFilterMask(rigid_body_->GetCollisionMask());
		CollisionCheck();
		rigid_body_->SetVelocity(0, 10 * gameTime);

		timer_+=gameTime;
		if (timer_ >= time_limit_)
		{
			timer_ = 0;
			current_health_ = 0;
		}
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
	case BOUNDS:
	{
		current_health_--;
		break;
	}

	case NONE:
		break;
	}
}

void Projectile::Reset() 	
{
	gef::Vector4 pos = parent_transform->GetPosition();
	Entity::Reset(pos);
}

Projectile::~Projectile()
{
}
