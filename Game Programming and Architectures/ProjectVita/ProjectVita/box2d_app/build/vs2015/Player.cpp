#include "Player.h"

Player::Player(GameObject& parent, gef::InputManager& inputManager) 
	: Component::Component(parent), 
	_inputManager(inputManager)
{	
	rigidbody = _gameObject.GetComponent<Rigidbody2D>();
	body = rigidbody->GetBody();
}

void Player::Update(float deltaTime)
{
	if (_inputManager.keyboard()->IsKeyDown(gef::Keyboard::KC_W))
	{
		body->ApplyForceToCenter(b2Vec2(0, 20), true);
	}

	if (_inputManager.keyboard()->IsKeyDown(gef::Keyboard::KC_A))
	{
		body->ApplyForceToCenter(b2Vec2(-1, 0), true);
	}

	if (_inputManager.keyboard()->IsKeyDown(gef::Keyboard::KC_S))
	{
		body->ApplyForceToCenter(b2Vec2(0, 0), true);
	}

	if (_inputManager.keyboard()->IsKeyDown(gef::Keyboard::KC_D))
	{
		body->ApplyForceToCenter(b2Vec2(1, 0), true);
	}
}

void Player::Render(gef::Renderer3D * renderer)
{
}


Player::~Player()
{
}
