#include "Player.h"
#include "maths\math_utils.h"

Player::Player(gef::InputManager& inputManager)
	: Entity::Entity()
	, _inputManager(inputManager)
{
	//rigidbody = _gameObject.GetComponent<Rigidbody2D>();
	//meshRenderer = _gameObject.GetComponent<MeshRenderer>();
	
	speed_ = 5;
}

void Player::Update(float deltaTime)
{
	Entity::Update(deltaTime);
	CollisionCheck();

	if (ammo_count == 0)
	{
		if (_inputManager.keyboard()->IsKeyPressed(gef::Keyboard::KC_SPACE))
		{
			projectile_->Fire();
			ammo_count--;
		}
	}

	for (int i = 0; i < ammo_cap; i++)
	{
		//if(i >= ammo_count)
		projectile_->Update(deltaTime);

		if (!projectile_->IsAlive())
		{
			projectile_->Reset();
			projectile_->Reload();
			ammo_count++;
		}
	}

	switch (projectile_->GetRigidBody()->GetCurrentColliding())
	{
	case ENEMY:
		score_ += 200;
		projectile_->GetRigidBody()->ToggleMask(projectile_->GetRigidBody()->GetCollisionMask());
		projectile_->GetRigidBody()->SetCurrentColliding(NONE);

		break;
	case ASTEROID:
		score_ += 50;
		projectile_->GetRigidBody()->ToggleMask(projectile_->GetRigidBody()->GetCollisionMask());
		projectile_->GetRigidBody()->SetCurrentColliding(NONE);
		break;
	default:
		break;
	}
	
/*
	if (ammo_count >= 0)
	{
		if (_inputManager.keyboard()->IsKeyDown(gef::Keyboard::KC_SPACE))
		{
			if (projectile_[ammo_count])
			{
				projectile_[ammo_count]->Fire();
				ammo_count -= 1;
			}
		}
		else
			projectile_[ammo_count]->SetParentTransform(tranform_);
	}

	for (int i = ammo_count; i < ammo_cap; i++)
	{
		projectile_[i]->Update(deltaTime);
		switch (projectile_[i]->GetRigidBody()->GetCurrentColliding())
		{
		case ENEMY:
			score_ += 2;
			projectile_[i]->GetRigidBody()->ToggleMask(ENEMY);

			break;
		case ASTEROID:
			score_ += 1;
			projectile_[i]->GetRigidBody()->ToggleMask(ASTEROID);
			break;
		default:
			break;
		}

		projectile_[i]->Reset();


	}*/

	if (_inputManager.keyboard()->IsKeyDown(gef::Keyboard::KC_W))  //check player is in height bounds
		rigid_body_->GetBody()->ApplyForceToCenter(b2Vec2(0, speed_ * deltaTime), true);	//allow y velocity
	else if (_inputManager.keyboard()->IsKeyDown(gef::Keyboard::KC_S))
		rigid_body_->GetBody()->ApplyForceToCenter(b2Vec2(0, -speed_ * deltaTime), true);
	
	if (_inputManager.keyboard()->IsKeyDown(gef::Keyboard::KC_A))//if input
	{
		//allow x velocity
		rigid_body_->GetBody()->ApplyForceToCenter(b2Vec2(-speed_ * deltaTime, 0), true);
		new_angle = left_angle_;
	}
	else if (_inputManager.keyboard()->IsKeyDown(gef::Keyboard::KC_D))//if input
	{
		//allow x velocity
		rigid_body_->GetBody()->ApplyForceToCenter(b2Vec2(speed_*deltaTime, 0), true);
		new_angle = right_angle_;
	}
	else
		new_angle = initial_angle_;
	
	current_angle_ = gef::Lerp(current_angle_, new_angle, 5 * deltaTime);
	mesh_renderer_->GetTransform()->SetRotationX(current_angle_);
}

void Player::Render(gef::Renderer3D * renderer)
{
	Entity::Render(renderer);
	projectile_->Render(renderer);
}


void Player::CollisionCheck()
{
	Entity::CollisionCheck();

	switch (rigid_body_->GetCurrentColliding())
	{
	case ASTEROID:
	{
		if (!IsIndestructable())
		{
			current_health_--;
			SetIndestructable(true);
		}
		//nothing
		break;
	}
	case ENEMY:
	{
		//current_health_--;
		break;
	}
	case NONE:
		break;
	}
}

void Player::SetProjectile(Projectile* projectile)
{
	
	projectile_ = projectile;
	projectile_->SetParentTransform(GetTransform());
	
}

Player::~Player()
{

}
