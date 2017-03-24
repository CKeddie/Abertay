#include "Player.h"
#include "maths\math_utils.h"

Player::Player(GameObject& parent, gef::InputManager& inputManager)
	: Entity::Entity(parent)
	, _inputManager(inputManager)
{
	rigidbody = _gameObject.GetComponent<Rigidbody2D>();
	meshRenderer = _gameObject.GetComponent<MeshRenderer>();

	body = rigidbody->GetBody();
	body->SetUserData(&_gameObject);
	speed_ = 20;
}

void Player::OnCollisionEnter()
{
	//body->ApplyLinearImpulseToCenter(b2Vec2(0, 20), true);
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
		if (objectA && objectB)
		{
			if (objectA->Tag == "Player" && objectB->Tag == "Enemy")
			{
				//body->ApplyForceToCenter(b2Vec2(0, 20), true);
			}
			//determine if contact A is a player and contact B is a ground object
			else if (objectA->Tag == "Player" && objectB->Tag == "Ground")
			{
				//body->ApplyForceToCenter(b2Vec2(0, 20), true);
			}
		}
	}

	if (_inputManager.keyboard()->IsKeyDown(gef::Keyboard::KC_W))  //check player is in height bounds
		body->ApplyForceToCenter(b2Vec2(0, speed_ * deltaTime), true);	//allow y velocity
	else if (_inputManager.keyboard()->IsKeyDown(gef::Keyboard::KC_S))
		body->ApplyForceToCenter(b2Vec2(0, -speed_ * deltaTime), true);
	
	if (_inputManager.keyboard()->IsKeyDown(gef::Keyboard::KC_A))//if input
	{
		//allow x velocity
		body->ApplyForceToCenter(b2Vec2(-speed_ * deltaTime, 0), true);
		new_angle = left_angle_;
	}
	else if (_inputManager.keyboard()->IsKeyDown(gef::Keyboard::KC_D))//if input
	{
		//allow x velocity
		body->ApplyForceToCenter(b2Vec2(speed_*deltaTime, 0), true);
		new_angle = right_angle_;
	}
	else
		new_angle = initial_angle_;

	current_angle_ = gef::Lerp(current_angle_, new_angle, 5 * deltaTime);
	meshRenderer->TiltX(gef::DegToRad(current_angle_));
}

void Player::Render(gef::Renderer3D * renderer)
{
}

Player::~Player()
{
}
