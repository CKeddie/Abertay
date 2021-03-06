#include "Entity.h"

Entity::Entity() 
	: GameObject()
{
	mesh_renderer_ = new MeshRenderer();
	rigid_body_ = new RigidBody();
	score_ = 0;
}

Entity::Entity(gef::Vector4 spawn) 
	: GameObject()
{
	spawn_point_ = spawn;	
	mesh_renderer_ = new MeshRenderer();
	rigid_body_ = new RigidBody();
	score_ = 0;
}


Entity::~Entity()
{
}

void Entity::Update(float gameTime)
{	
	// update after rigidbody calculations to make sure
	// the transform updates correctly
	GameObject::Update(gameTime); 
	
	//check to see if rigidbody exists
	if(rigid_body_)
		rigid_body_->Update(this);

	//check to see if mesh renderer exists
	if(mesh_renderer_)
		mesh_renderer_->Update(tranform_->GetTransform());

	if (IsIndestructable())
		indestructable_timer_+=gameTime;

	if (indestructable_timer_ > indestructable_limit_)
	{
		indestructable_timer_ = 0;
		SetIndestructable(false);
		rigid_body_->ResetMask();
	}

	if (!IsAlive() && !is_indestructable_)
	{
		rigid_body_->ToggleMask(rigid_body_->GetCollisionMask());
		is_indestructable_ = true;
	}
}

void Entity::CollisionCheck()
{
	//go through contacts
	b2ContactEdge* contacts = rigid_body_->GetBody()->GetContactList();
	rigid_body_->SetCurrentColliding(NONE);
	if (contacts)
	{
		uint16 flag = 0;
		uint16 A = contacts->contact->GetFixtureA()->GetFilterData().categoryBits;
		uint16 B = contacts->contact->GetFixtureB()->GetFilterData().categoryBits;
		uint16 C = (uint16)rigid_body_->GetCollisionCategory();

		if ((A ^ B))//if both a and b are different
		{
			//filter 
			if (A & C)//A is equal to self?
				flag |= B;//then is colliding with B
			else if (B & C)//B is equal to self?
				flag |= A;//collide with A
			else
				flag = 0;//otherwise no collision
		}
		else//if a and b are the same
			flag = A & B;

		rigid_body_->SetCurrentColliding((CollisionBitmask)(flag));//set the colliding with state
	}
}

void Entity::Render(gef::Renderer3D * renderer)
{
	//check to see if mesh renderer exists
	if(mesh_renderer_ && IsAlive())
		mesh_renderer_->Render(renderer);
}

void Entity::Reset()
{
	SetHealth(health_cap_);
	SetIndestructable(false);
	indestructable_timer_ = 0;
	rigid_body_->SetFilterMask(rigid_body_->GetCollisionMask());
	rigid_body_->SetPosition(spawn_point_);
}

void Entity::Reset(gef::Vector4 spawn)
{
	SetSpawnPoint(spawn);
	Entity::Reset();
}