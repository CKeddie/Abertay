#include "Player.h"

Player::Player(GameObject& parent, gef::InputManager& inputManager) 
	: Entity::Entity(parent), 
	_inputManager(inputManager)
{	
	rigidbody = _gameObject.GetComponent<Rigidbody2D>();
	body = rigidbody->GetBody();
	body->SetUserData(&_gameObject);
}

void Player::OnCollisionEnter()
{
	body->ApplyLinearImpulseToCenter(b2Vec2(0, 20), true);
	//body->ApplyForce(b2Vec2(0, 1000), body->GetPosition(), true);
}

void Player::OnCollisionExit()
{

}

void Player::Update(float deltaTime)
{
	//go through contacts
	b2ContactEdge* contacts = body->GetContactList();
	if (contacts)
	{
		void* bodyUserDataA = contacts->contact->GetFixtureA()->GetBody()->GetUserData();
		void* bodyUserDataB = contacts->contact->GetFixtureB()->GetBody()->GetUserData();

		GameObject* objectA = static_cast<GameObject*>(bodyUserDataA);
		GameObject* objectB = static_cast<GameObject*>(bodyUserDataB);

		//determine if contact A is a player and contact B is an enemy
		if (objectA->Tag == "Player" && objectB->Tag == "Enemy")
		{
			body->ApplyForceToCenter(b2Vec2(0, 20), true);
		}
		//determine if contact A is a player and contact B is a ground object
		else if (objectA->Tag == "Player" && objectB->Tag == "Ground")
		{
			//body->ApplyForceToCenter(b2Vec2(0, 20), true);
		}
	}

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
