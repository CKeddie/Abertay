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
	m_translate.SetIdentity();
	m_translate.SetTranslation(position);

	m_rotationX.SetIdentity();
	m_rotationX.RotationX(gef::DegToRad(rotation.x()));
	m_rotationY.SetIdentity();
	m_rotationY.RotationY(gef::DegToRad(rotation.y()));
	m_rotationZ.SetIdentity();
	m_rotationZ.RotationZ(gef::DegToRad(rotation.z()));

	m_scale.SetIdentity();
	m_scale.Scale(scale);
}


GameObject::~GameObject()
{

}

void GameObject::Update(float deltaTime)
{
	m_translate.SetTranslation(v_position);

	CalculateRotation();

	Vector4 forward = v_position + _forward;
	Vector4 up = v_position + _up;
	
	m_transform = m_translate * (m_rotationX * m_rotationY * m_rotationZ) * m_scale;	

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

void GameObject::DebugRenderer(gef::SpriteRenderer * spriteRenderer)
{
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

void GameObject::CalculateRotation()
{
	if (!(v_oldRotation == v_rotation))
	{
		_cosY = cosf(gef::DegToRad(v_rotation.y()));//x cos 
		_sinY = sinf(gef::DegToRad(v_rotation.y()));//x sin
		_cosP = cosf(gef::DegToRad(v_rotation.x()));//y cos
		_sinP = sinf(gef::DegToRad(v_rotation.x()));//y sin
		_cosR = cosf(gef::DegToRad(v_rotation.z()));//z cos
		_sinR = sinf(gef::DegToRad(v_rotation.z()));//z sin

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

		/*m_rotationX.RotationX(gef::DegToRad(v_rotation.x()));
		m_rotationY.RotationY(gef::DegToRad(v_rotation.y()));
		m_rotationZ.RotationZ(gef::DegToRad(v_rotation.z()));*/

	}	
}


