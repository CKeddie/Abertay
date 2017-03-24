#pragma once

#include <graphics\sprite_renderer.h>
#include <graphics\renderer_3d.h>
#include <maths\transform.h>
#include <Component.h>
#include <vector>
#include <algorithm>
#include <unordered_map>


using namespace std;
using namespace gef;

class GameObject
{
public:
	GameObject(const char* tag, Vector4 position = Vector4(), Vector4 rotation = Vector4(0,0,0), Vector4 scale = Vector4(1,1,1));
	~GameObject();

	virtual void Update(float deltaTime);
	virtual void Render(Renderer3D* renderer);

	void Pitch(float degrees);
	void Yaw(float degrees);
	void Roll(float degrees);
	
	void SetPosition(Vector4 position) { 
		v_position = position;
		translate_.SetTranslation(v_position);
	}
	Vector4 GetPosition() { return v_position; }
	
	void SetRotation(Vector4 rotation) { v_rotation = rotation; }
	Vector4 GetRotation() { return v_rotation; }
	
	void SetScale(Vector4 scale) { v_scale = scale; }
	Vector4 GetScale() { return v_scale; }
	Matrix44 GetTransformMatrix() { return transform_; }

	void AddComponent(Component* component) 
	{ 
		_components[&typeid(*component)] = component;
	}
	
	template <typename T> T* GetComponent() 
	{
		return static_cast<T*>(_components[&typeid(T)]);
	}

	string Tag;

protected:
	
	unordered_map < const type_info*, Component* > _components;

	Matrix44 transform_;
	Matrix44 rotation_x, rotation_y, rotation_z;
	Matrix44 scale_, translate_;

	Vector4 v_position = Vector4(), v_rotation = Vector4(), v_oldRotation = Vector4(), v_scale = Vector4();
	Vector4 _forward = Vector4(), _up = Vector4(), _right = Vector4(); //Local Axis
};

