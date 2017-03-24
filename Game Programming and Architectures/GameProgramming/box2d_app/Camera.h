#pragma once

#include "system\platform.h"
#include "scene_app.h"
#include "GameObject.h"

class Camera :
	public GameObject
{
public:
	Camera(Vector4 position, Vector4 rotation, Vector4 scale);
	~Camera();

	void Update(float deltaTime);
	void Render(Renderer3D* renderer, Platform & platform);

	void SetMovementSpeed(Vector4 moveSpeed) { _moveSpeed = moveSpeed; }
	void SetTurnSpeed(Vector4 turnSpeed) { _turnSpeed = turnSpeed; }

private:
	Vector4 _moveSpeed = Vector4(10, 10, 10), _turnSpeed = Vector4(1, 1, 1);
};

