#pragma once

#include "input\input_manager.h"
#include "input\keyboard.h"

#include "box2d\Box2D.h"

#include "Rigidbody2D.h"

#include "GameObject.h"
#include "Entity.h"

class GameObject;

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
	b2Body* body;
};

