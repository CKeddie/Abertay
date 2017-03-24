#include "GameObject.h"
#include "maths\math_utils.h"

GameObject::GameObject(const char * tag, Vector4 position, Vector4 rotation, Vector4 scale)
{
	Tag = tag;
	v_position = position;

	v_rotation = rotation;
	v_oldRotation = v_rotation + Vector4(1, 1, 1);
	v_scale = scale;

	//Initialize Matrices
	translate_.SetIdentity();
	translate_.SetTranslation(position);
	
	rotation_x.SetIdentity();
	rotation_x.RotationX(gef::DegToRad(rotation.x()));
	
	rotation_y.SetIdentity();
	rotation_y.RotationY(gef::DegToRad(rotation.y()));
	
	rotation_z.SetIdentity();
	rotation_z.RotationZ(gef::DegToRad(rotation.z()));

	scale_.SetIdentity();
	translate_.Scale(scale);
	
	transform_ = translate_ * rotation_x * rotation_y * rotation_z * scale_;
}


GameObject::~GameObject()
{

}

void GameObject::Update(float deltaTime)
{
	translate_.SetTranslation(v_position);

	rotation_x.SetIdentity();
	rotation_x.RotationX(gef::DegToRad(v_rotation.x()));

	rotation_y.SetIdentity();
	rotation_y.RotationY(gef::DegToRad(v_rotation.y()));

	rotation_z.SetIdentity();
	rotation_z.RotationZ(gef::DegToRad(v_rotation.z()));

	scale_.Scale(v_scale);

	transform_ = translate_ * rotation_x * rotation_y * rotation_z * scale_;
	
	for (auto& x : _components)//; i < _components.size(); i++)
	{
		x.second->Update(deltaTime);		
	}
}

void GameObject::Render(Renderer3D * renderer)
{
	for (auto& x : _components)//; i < _components.size(); i++)
	{
		x.second->Render(renderer);
	}
}

void GameObject::Pitch(float degrees)
{
	v_rotation.set_x(v_rotation.x() + degrees);
}

void GameObject::Yaw(float degrees)
{
	v_rotation.set_y(v_rotation.y() + degrees);
}

void GameObject::Roll(float degrees)
{
	v_rotation.set_z(v_rotation.z() + degrees);
}