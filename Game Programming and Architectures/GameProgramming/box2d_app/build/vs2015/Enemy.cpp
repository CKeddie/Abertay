#include "Enemy.h"
#include "maths\math_utils.h"
#include "GameObject.h"

Enemy::Enemy(GameObject& gameObject) : Entity(gameObject)
{
	current_health_ = 1;
	body = _gameObject.GetComponent<Rigidbody2D>()->GetBody();
}

void Enemy::Update(float gametime)
{	
	//go through contacts
	b2ContactEdge* contacts = body->GetContactList();
	if (contacts)
	{
		void* bodyUserDataA = contacts->contact->GetFixtureA()->GetBody()->GetUserData();
		void* bodyUserDataB = contacts->contact->GetFixtureB()->GetBody()->GetUserData();

		GameObject* objectA = static_cast<GameObject*>(bodyUserDataA);
		GameObject* objectB = static_cast<GameObject*>(bodyUserDataB);

		if (objectA == &this->_gameObject)
		{
			if (current_health_ > 0)
			{
				if (objectB->Tag == "Player")
				{
					current_health_--;
				}
				else if (objectB->Tag == "Asteroid")
				{
					current_health_--;
				}
			}
		}
		else if (objectB == &this->_gameObject)
		{
			if (objectA->Tag == "Player")
			{
				current_health_--;
			}
			else if (objectA->Tag == "Asteroid")
			{
				current_health_--;
			}
		}
	}

	if(current_health_ <= 0)
		_gameObject.GetComponent<MeshRenderer>()->TiltZ(_gameObject.GetComponent<Rigidbody2D>()->GetBody()->GetAngle());
}

void Enemy::SetDirection(gef::Vector4 target)
{	
	_gameObject.GetComponent<MeshRenderer>()->TiltZ(atan2(target_.y(), target_.x()));
	target_ = target - _gameObject.GetPosition();
	target_.Normalise();
	target_ *= 0.15f;
	_gameObject.GetComponent<Rigidbody2D>()->SetVelocity(target_.x(), target_.y());
}

Enemy::~Enemy()
{
}
