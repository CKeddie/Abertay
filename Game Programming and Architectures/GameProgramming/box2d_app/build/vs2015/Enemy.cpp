#include "Enemy.h"
#include "maths\math_utils.h"
#include "GameObject.h"
#include "Entity.h"

Enemy::Enemy()
	: Entity()
{

}

Enemy::Enemy(gef::Vector4 spawn)
	: Entity(spawn)
{

}

void Enemy::Update(float gametime) 
{	
	Entity::Update(gametime);
	CollisionCheck();
	if (angle >= right_angle)
		new_angle = left_angle;
	else if (angle <= left_angle)
		new_angle = right_angle;

	if (angle > new_angle)
		angle -= 100 * gametime;
	else
		angle += 100 * gametime;

	float dirX = cosf(gef::DegToRad(angle)) * 10 * gametime;
	float dirY = sinf(gef::DegToRad(angle)) * 5 * gametime;

	rigid_body_->SetVelocity(dirX, dirY);
	mesh_renderer_->GetTransform()->SetRotationZ(angle - 180);
}

void Enemy::CollisionCheck()
{
	Entity::CollisionCheck();
	switch (rigid_body_->GetCurrentColliding())
	{
	case PLAYER:
	{
		current_health_--;
		rigid_body_->ToggleMask((uint16)PLAYER);
		//nothing
		break;
	}
	case ASTEROID:
	{
		current_health_--;
		rigid_body_->ToggleMask((uint16)ASTEROID);
		break;
	}
	case PROJECTILE:
	{
		current_health_--;
		rigid_body_->ToggleMask((uint16)PROJECTILE);
		break;
	}
	case NONE:
		break;
	}	
}

void Enemy::SetDirection(gef::Vector4 target)
{	
	/*_gameObject.GetComponent<MeshRenderer>()->TiltZ(atan2(target_.y(), target_.x()));
	target_ = target - _gameObject.GetPosition();
	target_.Normalise();
	target_ *= 0.15f;
	_gameObject.GetComponent<Rigidbody2D>()->SetVelocity(target_.x(), target_.y());
	*/
}

Enemy::~Enemy()
{
}
