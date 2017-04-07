#pragma once

#include "system\platform.h"
#include "scene_app.h"
#include "GameObject.h"

class Camera :
	public GameObject
{
public:
	Camera(gef::Vector4 position, gef::Vector4 rotation, gef::Vector4 scale);
	~Camera();

	void Update(float deltaTime);
	void Render(gef::Renderer3D * renderer, gef::Platform & platform);

	void SetMovementSpeed(gef::Vector4 moveSpeed) { _moveSpeed = moveSpeed; }
	void SetTurnSpeed(gef::Vector4 turnSpeed) { _turnSpeed = turnSpeed; }

private:
	gef::Vector4 _moveSpeed = gef::Vector4(10, 10, 10), _turnSpeed = gef::Vector4(1, 1, 1);
};

