#pragma once

#include "input\input_manager.h"
#include "input\keyboard.h"

#include "box2d\Box2D.h"

#include "Entity.h"
#include "Projectile.h"

class GameObject;
class RigidBody2D;
class MeshRenderer;

class Player :
	public Entity
{
public:
	Player(gef::InputManager & inputManager);
	~Player();
	void Update(float deltaTime);
	void Render(gef::Renderer3D* renderer);
	void CollisionCheck();
	void SetProjectile(Projectile * projectile);
protected:
	gef::InputManager& _inputManager;
	float current_angle_ = 0, new_angle = 0, left_angle_ = 35, right_angle_ = -35, initial_angle_ = 0;
	Projectile* projectile_;
	int ammo_count = 0, ammo_cap = 1;
};

