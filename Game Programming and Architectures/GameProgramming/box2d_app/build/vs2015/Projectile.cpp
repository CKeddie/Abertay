#include "Projectile.h"
#include "GameObject.h"
#include "Rigidbody2D.h"


Projectile::Projectile(GameObject& parent) 
	: Component(parent)
{
}

void Projectile::Update(float gameTime)
{
	_gameObject.GetComponent<Rigidbody2D>()->SetVelocity(0,1);
}

Projectile::~Projectile()
{
}
