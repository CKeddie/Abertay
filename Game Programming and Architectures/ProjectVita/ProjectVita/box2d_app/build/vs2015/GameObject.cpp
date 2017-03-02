#include "GameObject.h"
#include "maths\math_utils.h"

GameObject::GameObject(Vector4 position, Vector4 rotation, Vector4 scale)
{
	v_rotation = rotation;
	v_position = position;
	v_scale = scale;

	CalculateLocalAxis();

	m_transform.SetTranslation(v_position);

	m_rotationX.RotationX(gef::DegToRad(v_rotation.x()));
	m_rotationY.RotationY(gef::DegToRad(v_rotation.y()));
	m_rotationZ.RotationZ(gef::DegToRad(v_rotation.z()));

	m_scale.Scale(v_scale);	

}

GameObject::~GameObject()
{

}

void GameObject::Update(float deltaTime)
{
	m_transform.SetTranslation(v_position);
	CalculateLocalAxis();
	m_scale.Scale(v_scale);

	m_transform = m_transform * m_rotationX * m_rotationY * m_rotationZ * m_scale;

	for (int i = 0; i < _components.size(); i++)
	{
		_components[i]->Update(deltaTime);
	}
}

void GameObject::Render(Renderer3D * renderer)
{
	for (int i = 0; i < _components.size(); i++)
	{
		_components[i]->Render(renderer);
	}
}

void GameObject::Rotate(Vector4 axis, float amount)
{
	m_rotationX.RotationX(v_rotation.x() + (axis.x() * amount));
	m_rotationY.RotationY(v_rotation.y() + (axis.y() * amount));
	m_rotationZ.RotationZ(v_rotation.z() + (axis.z() * amount));
}

void GameObject::Pitch(float degrees)
{
	v_rotation.set_x(v_rotation.x() + degrees);
	m_rotationX.RotationX(gef::DegToRad(v_rotation.x()));
}

void GameObject::Yaw(float degrees)
{
	v_rotation.set_y(v_rotation.y() + degrees);
	m_transform.RotationY(gef::DegToRad(v_rotation.y()));
}

void GameObject::Roll(float degrees)
{
	v_rotation.set_z(v_rotation.z() + degrees);
	m_rotationZ.RotationZ(gef::DegToRad(v_rotation.z()));
}

void GameObject::MoveForwards(float amount)
{
	v_position += _forward * amount;
}
void GameObject::MoveRight(float amount)
{
	v_position += _right * amount;
}
void GameObject::MoveUp(float amount)
{
	v_position += _up * amount;
}
void GameObject::MoveTowards(Vector4 axis, float amount)
{
	v_position += axis * amount;
}

void GameObject::CalculateLocalAxis()
{
	if (!(v_oldRotation == v_rotation))
	{
		_cosY = cosf(v_rotation.y() * 3.1415f / 180);//x cos 
		_sinY = sinf(v_rotation.y() * 3.1415f / 180);//x sin	

		_cosP = cosf(v_rotation.x() * 3.1415f / 180);//y cos
		_sinP = sinf(v_rotation.x() * 3.1415f / 180);//y sin	

		_cosR = cosf(v_rotation.z() * 3.1415f / 180);//z cos
		_sinR = sinf(v_rotation.z() * 3.1415f / 180);//z sin

		_up.set_x((-_cosY * _sinR) - (_sinY * _sinP * _cosR));
		_up.set_y(_cosP * _cosR);
		_up.set_z((-_sinY * _sinR) - (_sinP * _cosR * -_cosY));
		_up.Normalise();

		_forward.set_x(_sinY * _cosP);
		_forward.set_y(_sinP);
		_forward.set_z(_cosP * -_cosY);
		_forward.Normalise();

		_right.set_x((_up.y() * _forward.z()) - (_up.z() * _forward.y()));
		_right.set_y((_up.z() * _forward.x()) - (_up.x() * _forward.z()));
		_right.set_z((_up.x() * _forward.y()) - (_up.y() * _forward.x()));
		_right.Normalise();

		v_oldRotation = v_rotation;
	}
	m_transform.LookAt(v_position, v_position + _forward, _up);
}


