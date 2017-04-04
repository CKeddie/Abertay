#pragma once
#include "Component.h"
#include "Box2D\Box2D.h"

class GameObject;

enum CollisionBitmask
{
	BOUNDS = 0x0001,
	ENEMY = 0x0002,
	PLAYER = 0x0004,
	ASTEROID = 0x0008,
	PROJECTILE = 0x0010
};

class Rigidbody2D :
	public Component
{
public:
	Rigidbody2D(GameObject & parent, b2World * world, b2BodyType type, float sizeX, float sizeY, uint16 categoryMask, uint16 bitmask);
	//Rigidbody2D(GameObject & parent, b2World * world, b2BodyDef * bodyDefinition, b2PolygonShape * shape, b2FixtureDef * fixture);
	void Update(float deltaTime);
	void Render(gef::Renderer3D* renderer);
	void SetPosition(gef::Vector4 position) { _body->SetTransform(b2Vec2(position.x(), position.y()), 0.0f); }
	void SetDrag(float scale);
	void SetVelocity(float x, float y) { _body->SetLinearVelocity(b2Vec2(x, y)); }
	void SetAngularVelocity(float amount) { _body->SetAngularVelocity(amount); }
	b2Vec2 GetVelocity() { return _body->GetLinearVelocity(); }
	
	b2Body* GetBody() { return _body; }
	~Rigidbody2D();

protected:
	b2World* _world;
	b2Body* _body;
	b2BodyDef bodyDef;
	b2PolygonShape shape;
	b2FixtureDef fixture;
	b2Vec2 _velocity;
	uint16 bitmask_;
	//b2BodyDef _bodyDef;
};

