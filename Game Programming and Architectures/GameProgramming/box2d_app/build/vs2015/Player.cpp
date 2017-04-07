#include "Player.h"
#include "maths\math_utils.h"

Player::Player(gef::InputManager& inputManager)
	: Entity::Entity()
	, _inputManager(inputManager)
{
	//rigidbody = _gameObject.GetComponent<Rigidbody2D>();
	//meshRenderer = _gameObject.GetComponent<MeshRenderer>();

	speed_ = 1;
}

void Player::Update(float deltaTime)
{
	Entity::Update(deltaTime);
	CollisionCheck();

	if (_inputManager.keyboard()->IsKeyDown(gef::Keyboard::KC_SPACE))
	{
		if (projectile_)
		{
			projectile_->Fire();
		}
	}
	else
		projectile_->SetParentTransform(tranform_);

	projectile_->Update(deltaTime);

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
	if (projectile_ && IsAlive())
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
}

Player::~Player()
{

}
