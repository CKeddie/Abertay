#include "Camera.h"
#include "maths\math_utils.h"

Camera::Camera(gef::Vector4 position, gef::Vector4 rotation, gef::Vector4 scale) : GameObject()
{
}

Camera::~Camera()
{
}

void Camera::Update(float deltaTime)
{
	GameObject::Update(deltaTime);
}

void Camera::Render(gef::Renderer3D * renderer, gef::Platform &platform)
{
	GameObject::Render(renderer);

	float fov = gef::DegToRad(60.0f);
	float aspect_ratio = (float)platform.width() / (float)platform.height();

	gef::Matrix44 projection_matrix;
	projection_matrix = platform.PerspectiveProjectionFov(fov, aspect_ratio, 0.1f, 100.0f);

	renderer->set_projection_matrix(projection_matrix);
	tranform_->GetTransform().LookAt(tranform_->GetPosition(), gef::Vector4(0, 0, 0), gef::Vector4(0, 1, 0));
	renderer->set_view_matrix(tranform_->GetTransform());
}
