#pragma once

#include "Component.h"
#include "GameObject.h"
#include <graphics\renderer_3d.h>
#include <box2d\Box2D.h>

enum CollisionBitmask
{
	NONE = 0x0000,
	BOUNDS = 0x0001,
	ENEMY = 0x0002,
	PLAYER = 0x0004,
	ASTEROID = 0x0008,
	PROJECTILE = 0x0010
};

class RigidBody : public Component
{
public:
	RigidBody();
	~RigidBody();
	void Initialize(GameObject * gameObject, b2World * world, b2BodyType type, float sizeX, float sizeY, uint16 categoryMask, uint16 bitmask);
	void Update(GameObject* gameObject);
	void SetPosition(gef::Vector4 position) { _body->SetTransform(b2Vec2(position.x(), position.y()), 0.0f); }
	void SetVelocity(float x, float y) { _body->SetLinearVelocity(b2Vec2(x, y)); }
	void SetAngularVelocity(float amount) { _body->SetAngularVelocity(amount); }
	void ApplyForce(float x, float y);
	b2Vec2 GetVelocity() { return _body->GetLinearVelocity(); }
	b2Body* GetBody() { return _body; }
	CollisionBitmask GetCollisionMask() { return bitmask_; }
	CollisionBitmask GetCollisionCategory() { return category_; }

	CollisionBitmask GetCurrentColliding() { return current_colliding_; }
	void SetCurrentColliding(CollisionBitmask mask) { current_colliding_ = mask; }
protected:
	b2World* _world;
	b2Body* _body;
	b2BodyDef bodyDef;
	b2PolygonShape shape;
	b2FixtureDef fixture;
	b2Vec2 _velocity;
	CollisionBitmask bitmask_;
	CollisionBitmask category_;
	CollisionBitmask current_colliding_ = NONE;
};

