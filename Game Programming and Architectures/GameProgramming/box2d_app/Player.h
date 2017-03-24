#pragma once

#include "input\input_manager.h"
#include "input\keyboard.h"

#include "box2d\Box2D.h"

#include "GameObject.h"
#include "Entity.h"

#include "MeshRenderer.h"
#include "Rigidbody2D.h"

class GameObject;
class RigidBody2D;
class MeshRenderer;

class Player :
	public Entity
{
public:
	Player(GameObject & parent, gef::InputManager & inputManager);
	void OnCollisionEnter();
	void OnCollisionExit();
	void Update(float deltaTime);
	void Render(gef::Renderer3D* renderer);
	
	~Player();
protected:
	gef::InputManager& _inputManager;
	Rigidbody2D* rigidbody;
	MeshRenderer* meshRenderer;
	b2Body* body;

	float current_angle_ = 0, new_angle = 0, left_angle_ = 25, right_angle_ = -25, initial_angle_ = 0;
};

