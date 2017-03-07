#pragma once
#include "Component.h"
#include "Box2D\Box2D.h"

class GameObject;

class Rigidbody2D :
	public Component
{
public:
	Rigidbody2D(GameObject & parent, b2World * world, b2BodyType type, float sizeX, float sizeY);
	//Rigidbody2D(GameObject & parent, b2World * world, b2BodyDef * bodyDefinition, b2PolygonShape * shape, b2FixtureDef * fixture);
	void Update(float deltaTime);
	void Render(gef::Renderer3D* renderer);
	b2Body* GetBody() { return _body; }
	~Rigidbody2D();

protected:
	b2World* _world;
	b2Body* _body;
	b2BodyDef bodyDef;
	b2PolygonShape shape;
	b2FixtureDef fixture;
	//b2BodyDef _bodyDef;
};

