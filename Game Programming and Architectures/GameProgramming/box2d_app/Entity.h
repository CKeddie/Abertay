#pragma once
#include "Component.h"

class MeshRenderer;
class Rigidbody2D;

class Entity :
	public Component
{
public:
	Entity(GameObject & parent);
	void Update(float deltaTime);
	void Render(gef::Renderer3D* renderer);
	~Entity();

	void SetSpawnPoint(gef::Vector4 spawn) { spawn_point_ = spawn; }

	void SetSpeed(float speed) { speed_ = speed; }

	void Reset();
	void Reset(gef::Vector4);

	int GetHealth() { return current_health_; };
	void SetHealth(int value) { current_health_ = value; }

	bool IsAlive() { return (current_health_ > 0); }

	bool IsIndestructable() { return is_indestructable_; }
	void SetIndestructable(bool value) { is_indestructable_ = value; }
protected:
	int current_health_ = 1, health_cap_ = 1;
	float speed_ = 15;
	bool is_indestructable_ = false;
	gef::Vector4 spawn_point_;
	Rigidbody2D* rigid_body_;
	MeshRenderer* mesh_renderer_;

};

