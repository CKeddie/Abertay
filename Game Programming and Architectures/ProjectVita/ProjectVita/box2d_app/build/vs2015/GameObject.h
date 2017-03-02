#pragma once

#include "graphics\renderer_3d.h"
#include "maths\transform.h"
#include "Component.h"
#include <vector>
#include <algorithm>

using namespace std;
using namespace gef;

class GameObject
{
public:
	GameObject(Vector4 position = Vector4(), Vector4 rotation = Vector4(), Vector4 scale = Vector4(1,1,1));
	~GameObject();

	virtual void Update(float deltaTime);
	virtual void Render(Renderer3D* renderer);

	void Rotate(Vector4 axis, float amount);
	void Pitch(float degrees);
	void Yaw(float degrees);
	void Roll(float degrees);

	void MoveForwards(float amount);
	void MoveRight(float amount);
	void MoveUp(float amount);
	void MoveTowards(Vector4 axis, float amount);
	void CalculateLocalAxis();

	void AddComponent(Component* component) { _components.push_back(component); }
	Component* GetComponent(int index) { return _components[index]; }

	Matrix44 GetTransformMatrix() { return m_transform; }

protected:
	vector<Component*> _components;

	Matrix44 m_rotationX, m_rotationY, m_rotationZ;
	Matrix44 m_scale, m_transform; // GameObject Transform Matrix	

	Vector4 v_position, v_rotation, v_oldRotation, v_scale;

	Vector4 _forward, _up, _right; //Local Axis

private:
	float _cosY, _sinY, // Yaw
		  _cosP, _sinP, // Pitch
		  _cosR, _sinR;	// Roll
};

