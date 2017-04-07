#include "RigidBody.h"



RigidBody::RigidBody()
	: _body(NULL)
{

}

RigidBody::~RigidBody()
{
}

void RigidBody::Initialize(GameObject* gameObject, b2World * world, b2BodyType type, float sizeX, float sizeY, uint16 categoryMask, uint16 bitmask)
{
	//this = new RigidBody();
	category_ = (CollisionBitmask)categoryMask;
	bitmask_ = (CollisionBitmask)bitmask;
	_world = world;
	bodyDef.type = type;
	bodyDef.position = b2Vec2
	(
		gameObject->GetTransform()->GetPosition().x(),
		gameObject->GetTransform()->GetPosition().y()
	);

	float x = sizeX;
	float y = sizeY;
	shape.SetAsBox(x, y);

	fixture.density = powf(sizeX + sizeY, 3);
	fixture.shape = &shape;
	fixture.filter.categoryBits = categoryMask;
	fixture.filter.maskBits = bitmask;

	_body = world->CreateBody(&bodyDef);
	_body->CreateFixture(&fixture);
	_body->SetUserData(&category_);
}


void RigidBody::Update(GameObject* gameObject)
{
	if (_body->GetType() == b2_staticBody)
		return;

	gef::Vector4 translation(_body->GetPosition().x, _body->GetPosition().y, 0.0f);
	_velocity = _body->GetLinearVelocity();
	gameObject->GetTransform()->SetPosition(translation);
}

void RigidBody::ApplyForce(float x, float y)
{
	_body->ApplyForceToCenter(b2Vec2(x, y), true);
}

