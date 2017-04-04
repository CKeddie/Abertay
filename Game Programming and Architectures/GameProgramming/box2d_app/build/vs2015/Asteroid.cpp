#include "Asteroid.h"
#include "Rigidbody2D.h"
#include "GameObject.h"
#include "MeshRenderer.h"

Asteroid::Asteroid(GameObject & parent) : Entity(parent)
{
}

void Asteroid::Update(float gameTime)
{
	//Reset();
	//_gameObject.GetComponent<Rigidbody2D>()->SetPosition(gef::Vector4(0, 0, 0));
	_gameObject.GetComponent<MeshRenderer>()->TiltZ(_gameObject.GetComponent<Rigidbody2D>()->GetBody()->GetAngle());
}


Asteroid::~Asteroid()
{
}
