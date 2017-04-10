#pragma once

#include <GameObject.h>
#include <MeshRenderer.h>
#include <RigidBody.h>

class Entity : public GameObject
{
public:
	Entity();
	Entity(gef::Vector4 spawn);
	~Entity();
	void Update(float gameTime);
	virtual void CollisionCheck();
	void Render(gef::Renderer3D* renderer);
	RigidBody* GetRigidBody() { return rigid_body_; }
	MeshRenderer* GetMeshRenderer() { return mesh_renderer_; }
	void SetSpawnPoint(gef::Vector4 spawn) { spawn_point_ = spawn; }

	float GetSpeed() { return speed_; }
	void SetSpeed(float speed) { speed_ = speed; }
	
	virtual void Reset();
	virtual void Reset(gef::Vector4);

	int GetHealth() { return current_health_; };
	void SetHealth(int value) { current_health_ = value; }

	bool IsAlive() { return (current_health_ > 0); }

	bool IsIndestructable() { return is_indestructable_; }
	void SetIndestructable(bool value) { is_indestructable_ = value; }

	int GetScore() { return score_; }
	void AddScore(int amount) { score_ += amount; }
	void RemoveScore(int amount) { score_ -= amount; }

protected:
	int current_health_ = 1, health_cap_ = 1;
	float speed_ = 15;
	bool is_indestructable_ = false;
	gef::Vector4 spawn_point_;
	RigidBody* rigid_body_;
	MeshRenderer* mesh_renderer_;
	float indestructable_timer_ = 0, indestructable_limit_ = 2;
	int score_ = 0;
};

