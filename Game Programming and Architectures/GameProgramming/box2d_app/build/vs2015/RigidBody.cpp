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

	fixture.density = 2;
	fixture.shape = &shape;

	_filterData.categoryBits = categoryMask;
	_filterData.maskBits = bitmask;
		
	_body = world->CreateBody(&bodyDef);
	_body->CreateFixture(&fixture);
	_body->SetUserData(&category_);
	_body->GetFixtureList()->SetFilterData(_filterData);
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

void RigidBody::ToggleMask(uint16 collisionType)
{
	uint16 flags = (uint16)bitmask_;
	flags ^= collisionType;
	CollisionBitmask bm = (CollisionBitmask)flags;
	_filterData.maskBits  =  (CollisionBitmask)flags;
	_body->GetFixtureList()->SetFilterData(_filterData);
	_filterData.maskBits ^= (CollisionBitmask)collisionType;
}

void RigidBody::ResetMask()
{
	_body->GetFixtureList()->SetFilterData(_filterData);
}
