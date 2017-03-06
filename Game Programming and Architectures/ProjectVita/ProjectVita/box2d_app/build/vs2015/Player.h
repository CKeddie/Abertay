#pragma once
#include "Component.h"
#include "input\input_manager.h"
#include "input\keyboard.h"

class Player :
	public Component
{
public:
	Player(GameObject & parent, gef::InputManager & inputManager);
	void Update(float deltaTime);
	void Render(gef::Renderer3D* renderer);
	~Player();
protected:
	gef::InputManager& _inputManager;
};

