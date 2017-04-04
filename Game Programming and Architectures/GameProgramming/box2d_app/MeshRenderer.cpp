#include "MeshRenderer.h"
#include "GameObject.h"


MeshRenderer::MeshRenderer(GameObject & gameObject, gef::Mesh * mesh, gef::Material * material = NULL, gef::Vector4 rotation = Vector4(0, 0, 0))
	: Component::Component(gameObject)
	, _meshInstance(NULL)
	, _material(material)
{
	_meshInstance = new MeshInstance();
	_meshInstance->set_mesh(mesh);

	transform_.SetIdentity();
	translation_.SetIdentity();
	pitch_.RotationX(gef::DegToRad(rotation.x()));
	yaw_.RotationY(gef::DegToRad(rotation.y()));
	roll_.RotationZ(gef::DegToRad(rotation.z()));
	transform_ = translation_ * pitch_ * yaw_ * roll_;
}

MeshRenderer::MeshRenderer(GameObject & gameObject, gef::Mesh * mesh, gef::Material * material, gef::Vector4 rotation, gef::Vector4 position)
	: Component::Component(gameObject)
	, _meshInstance(NULL)
	, _material(material)
{
	_meshInstance = new MeshInstance();
	_meshInstance->set_mesh(mesh);

	transform_.SetIdentity();
	translation_.SetIdentity();
	translation_.SetTranslation(position);
	pitch_.RotationX(gef::DegToRad(rotation.x()));
	yaw_.RotationY(gef::DegToRad(rotation.y()));
	roll_.RotationZ(gef::DegToRad(rotation.z()));
	transform_ = translation_ * pitch_ * yaw_ * roll_;
}
void MeshRenderer::TiltZ(float radians)
{
	roll_.RotationZ(radians);
}

void MeshRenderer::TiltY(float radians)
{
	yaw_.RotationY(radians);
}

void MeshRenderer::TiltX(float radians)
{
	pitch_.RotationX(radians);
}

void MeshRenderer::Update(float deltaTime)
{
	transform_ = translation_ * pitch_ * yaw_ * roll_ ;
	_meshInstance->set_transform(transform_ * _gameObject.GetTransformMatrix());
}

void MeshRenderer::Render(gef::Renderer3D * renderer)
{
	//renderer->set_override_material(_material);
	if(IsDrawable())
		renderer->DrawMesh(*_meshInstance);
}


MeshRenderer::~MeshRenderer()
{
}
