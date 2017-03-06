#include "Rigidbody2D.h"

Rigidbody2D::Rigidbody2D(GameObject & parent, b2World * world, b2BodyType type, float sizeX, float sizeY)
	: Component::Component(parent),
	_body(NULL)
{
	bodyDef.type = type;
	bodyDef.position = b2Vec2(_gameObject.GetPosition().x(), _gameObject.GetPosition().y());

	float x = sizeX;
	float y = sizeY;
	shape.SetAsBox(x, y);

	fixture.density = powf(sizeX + sizeY, 3);
	fixture.shape = &shape;

	_body = world->CreateBody(&bodyDef);
	_body->CreateFixture(&fixture);
}

void Rigidbody2D::Update(float deltaTime)
{
	if (_body->GetType() == b2_staticBody)
		return;

	Vector4 translation(_body->GetPosition().x, _body->GetPosition().y, 0.0f);
	_gameObject.SetPosition(translation);
}

void Rigidbody2D::Render(gef::Renderer3D * renderer)
{

}

Rigidbody2D::~Rigidbody2D()
{
	
}
