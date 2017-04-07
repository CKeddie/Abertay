#include "Enemy.h"
#include "maths\math_utils.h"
#include "GameObject.h"
#include "Entity.h"

Enemy::Enemy() : Entity()
{
	//current_health_ = 1;
	//body = _gameObject.GetComponent<Rigidbody2D>()->GetBody();
}

void Enemy::Update(float gametime) 
{	
	Entity::Update(gametime);
	CollisionCheck();
	//if(current_health_ <= 0)
	//	_gameObject.GetComponent<MeshRenderer>()->TiltZ(_gameObject.GetComponent<Rigidbody2D>()->GetBody()->GetAngle());
}

void Enemy::CollisionCheck()
{
	Entity::CollisionCheck();
	switch (rigid_body_->GetCurrentColliding())
	{
	case PLAYER:
	{
		//current_health_--;
		//nothing
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
