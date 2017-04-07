#include "Transform.h"

Transform::Transform()
{
	position_ = gef::Vector4(0, 0, 0);
	rotation_ = gef::Vector4(0, 0, 0);
	scale_ = gef::Vector4(1, 1, 1);

	translation_matrix_.SetIdentity();

	rotation_matrix_x_.SetIdentity();
	rotation_matrix_y_.SetIdentity();
	rotation_matrix_z_.SetIdentity();

	scale_matrix_.SetIdentity();
	
}

Transform::~Transform()
{

}

void Transform::Initialize(gef::Vector4 position = gef::Vector4(0, 0, 0), gef::Vector4 rotation = gef::Vector4(0, 0, 0), gef::Vector4 scale = gef::Vector4(1, 1, 1))
{
	position_ = position;
	rotation_ = rotation;
	scale_ = scale;

	translation_matrix_.SetIdentity();

	rotation_matrix_x_.SetIdentity();
	rotation_matrix_y_.SetIdentity();
	rotation_matrix_z_.SetIdentity();

	scale_matrix_.SetIdentity();
}

void Transform::UpdateMatrices()
{	
	translation_matrix_.SetTranslation(position_);

	rotation_matrix_x_.RotationX(gef::DegToRad(rotation_.x()));
	rotation_matrix_y_.RotationY(gef::DegToRad(rotation_.y()));
	rotation_matrix_z_.RotationZ(gef::DegToRad(rotation_.z()));

	scale_matrix_.Scale(scale_);

	transform_matrix_ = translation_matrix_ * rotation_matrix_x_ * rotation_matrix_y_* rotation_matrix_z_ * scale_matrix_;
}