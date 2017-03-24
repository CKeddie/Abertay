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

void Camera::Render(Renderer3D * renderer, Platform &platform)
{
	GameObject::Render(renderer);

	float fov = gef::DegToRad(60.0f);
	float aspect_ratio = (float)platform.width() / (float)platform.height();

	gef::Matrix44 projection_matrix;
	projection_matrix = platform.PerspectiveProjectionFov(fov, aspect_ratio, 0.1f, 100.0f);

	renderer->set_projection_matrix(projection_matrix);
	transform_.LookAt(v_position, gef::Vector4(0, 0, 0), gef::Vector4(0, 1, 0));
	renderer->set_view_matrix(transform_);
}
