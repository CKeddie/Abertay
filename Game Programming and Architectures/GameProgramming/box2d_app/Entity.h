#pragma once
#include "Component.h"

class Entity :
	public Component
{
public:
	Entity(GameObject & parent);
	void Update(float deltaTime);
	void Render(gef::Renderer3D* renderer);
	~Entity();

	void SetSpeed(float speed) { speed_ = speed; }
	void Reset();
	int GetHealth() { return current_health_; };
	bool IsAlive() { return (current_health_ > 0); }

protected:
	int current_health_ = 1, health_cap_ = 1;
	float speed_ = 15;

};

