#include "GameObject.h"
#include "maths\math_utils.h"

GameObject::GameObject(Vector4 position, Vector4 rotation, Vector4 scale)
{
	_rotation = rotation;
	_position = position;
	_scale = scale;

	_transformMatrix.SetTranslation(_position);
	_transformMatrix.RotationX(gef::DegToRad(_rotation.x()));
	_transformMatrix.RotationY(gef::DegToRad(_rotation.y()));
	_transformMatrix.RotationZ(gef::DegToRad(_rotation.z()));
	_transformMatrix.Scale(_scale);	
}


GameObject::~GameObject()
{
}

void GameObject::Update(float deltaTime)
{
	//Remove
	//Yaw(5);
	//
	_transformMatrix.SetTranslation(_position);
	CalculateLocalAxis();
	_transformMatrix.Scale(_scale);

	for (int i = 0; i < _components.size(); i++)
	{
		_components[i].Update(deltaTime);
	}
}

void GameObject::Render(Renderer3D * renderer)
{
	for (int i = 0; i < _components.size(); i++)
	{
		_components[i].Render(renderer);
	}
}

void GameObject::Rotate(Vector4 axis, float amount)
{
	_rotation.set_x(_rotation.x() + (axis.x() * amount));
	_rotation.set_y(_rotation.y() + (axis.y() * amount));
	_rotation.set_z(_rotation.z() + (axis.z() * amount));
}

void GameObject::Pitch(float degrees)
{
	_rotation.set_x(_rotation.x() + degrees);
	_transformMatrix.RotationX(gef::DegToRad(_rotation.x()));
	//_rotation.set_x(gef::RadToDeg(atan2(_forward.x(), _forward.y())) * degrees);
}

void GameObject::Yaw(float degrees)
{
	//_rotation.set_y(gef::RadToDeg(atan2(_forward.z(), _forward.x())) * degrees);
	_rotation.set_y(_rotation.y() + degrees);
	_transformMatrix.RotationY(gef::DegToRad(_rotation.y()));
}

void GameObject::Roll(float degrees)
{
	_rotation.set_z(_rotation.z() + degrees);
	//_rotation.set_z(_rotation.z() + degrees);
	_transformMatrix.RotationZ(gef::DegToRad(_rotation.z()));
}

void GameObject::MoveForwards(float amount)
{
	_position += _forward * amount;
}

void GameObject::MoveRight(float amount)
{
	_position += _right * amount;
}

void GameObject::MoveUp(float amount)
{
	_position += _up * amount;
}

void GameObject::MoveTowards(Vector4 axis, float amount)
{
	_position += axis * amount;
}

void GameObject::CalculateLocalAxis()
{
	if (!(_oldRotation == _rotation))
	{
		_cosY = cosf(_rotation.y() * 3.1415f / 180);//x cos 
		_sinY = sinf(_rotation.y() * 3.1415f / 180);//x sin	

		_cosP = cosf(_rotation.x() * 3.1415f / 180);//y cos
		_sinP = sinf(_rotation.x() * 3.1415f / 180);//y sin	

		_cosR = cosf(_rotation.z() * 3.1415f / 180);//z cos
		_sinR = sinf(_rotation.z() * 3.1415f / 180);//z sin

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

		_oldRotation = _rotation;
}

	//_transformMatrix.LookAt(_position, _position + _forward, _position + _up);
}




