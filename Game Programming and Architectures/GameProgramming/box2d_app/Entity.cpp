#include "Entity.h"
#include "Rigidbody2D.h"
#include "GameObject.h"
#include "MeshRenderer.h"

Entity::Entity(GameObject & parent) : Component::Component(parent)
{
	SetSpawnPoint( parent.GetPosition() );
	mesh_renderer_ = _gameObject.GetComponent<MeshRenderer>();
}

Entity::~Entity()
{
}

void Entity::Reset()
{
	_gameObject.GetComponent<Rigidbody2D>()->SetPosition(spawn_point_);
	Vector4 v = spawn_point_;
	v.Normalise();
	float r = 0.25f;// static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	_gameObject.GetComponent<Rigidbody2D>()->SetAngularVelocity(0.0f);
	//r = r <= 0 ? r + 0.1f : r;
	_gameObject.GetComponent<Rigidbody2D>()->SetVelocity(-v.x() * r, -v.y() * r);
	SetHealth(health_cap_);
}

void Entity::Reset(gef::Vector4 spawn)
{
	SetSpawnPoint(spawn);
	Reset();
}

void Entity::Update(float deltaTime)
{
	if (mesh_renderer_)
		if(mesh_renderer_->IsDrawable() != IsAlive())
			mesh_renderer_->SetDrawable(IsAlive());

}

void Entity::Render(gef::Renderer3D * renderer)
{

}
