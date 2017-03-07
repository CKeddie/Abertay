#include "Camera.h"
#include "maths\math_utils.h"

Camera::Camera(Vector4 position, Vector4 rotation, Vector4 scale) : GameObject("Camera", position, rotation, scale)
{
}

Camera::~Camera()
{
}

void Camera::Update(float deltaTime)
{
	GameObject::Update(deltaTime);
}

void Camera::LockTo(GameObject* gameObject)
{
	v_position.set_x(gameObject->GetPosition().x());
	v_position.set_y(gameObject->GetPosition().y());
}

void Camera::Input(Keyboard* kb, float deltaTime)
{
	//Forwards/Backwards
	if (kb->IsKeyDown(gef::Keyboard::KC_DOWN))
	{
		MoveForwards(-_moveSpeed.z() * deltaTime);
	}
	else if (kb->IsKeyDown(gef::Keyboard::KC_UP))
	{
		MoveForwards(_moveSpeed.z() * deltaTime);
	}

	//Left/Right
	if (kb->IsKeyDown(gef::Keyboard::KC_RIGHT))
	{
		MoveRight(-_moveSpeed.x() * deltaTime);
	}
	else if (kb->IsKeyDown(gef::Keyboard::KC_LEFT))
	{
		MoveRight(_moveSpeed.x() * deltaTime);
	}

	//Up/Down
	if (kb->IsKeyDown(gef::Keyboard::KC_NUMPAD1))
	{
		MoveUp(-_moveSpeed.x() * deltaTime);
	}
	else if (kb->IsKeyDown(gef::Keyboard::KC_NUMPAD3))
	{
		MoveUp(_moveSpeed.x() * deltaTime);
	}

	//Yaw
	if (kb->IsKeyDown(gef::Keyboard::KC_NUMPAD4))
	{
		Yaw(-_turnSpeed.y());
	}
	else if (kb->IsKeyDown(gef::Keyboard::KC_NUMPAD6))
	{
		Yaw(_turnSpeed.y());
	}

	//Pitch
	if (kb->IsKeyDown(gef::Keyboard::KC_NUMPAD8))
	{
		Pitch(_turnSpeed.x());
	}
	else if (kb->IsKeyDown(gef::Keyboard::KC_NUMPAD2))
	{
		Pitch(-_turnSpeed.x());
	}

	//Roll
	if (kb->IsKeyDown(gef::Keyboard::KC_NUMPAD7))
	{
		Roll(-_turnSpeed.z());
	}
	else if (kb->IsKeyDown(gef::Keyboard::KC_NUMPAD9))
	{
		Roll(_turnSpeed.z());
	}
}

void Camera::Render(Renderer3D * renderer, Platform &platform)
{
	GameObject::Render(renderer);

	float fov = gef::DegToRad(45.0f);
	float aspect_ratio = (float)platform.width() / (float)platform.height();

	gef::Matrix44 projection_matrix;
	projection_matrix = platform.PerspectiveProjectionFov(fov, aspect_ratio, 0.1f, 100.0f);

	renderer->set_projection_matrix(projection_matrix);
	m_lookAt.LookAt(v_position, v_position + _forward, _up);
	renderer->set_view_matrix(m_lookAt);
}
