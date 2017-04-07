#pragma once

#include "maths\vector4.h"
#include "maths\matrix44.h"
#include "maths\math_utils.h"
#include "Component.h"
/*
Transform 
Serves as a base component to be used in all objects requiring movement, scaling, or rotations.
*/
class Transform : public Component
{
public:
	Transform();
	~Transform();

	void Initialize(gef::Vector4 position, gef::Vector4 rotation, gef::Vector4 scale);
	void UpdateMatrices();
	
	//Getters and Setters
	//Position
	gef::Vector4 GetPosition() { return position_; }
	void SetPosition(gef::Vector4 position) { position_ = position; }
	void SetPosition(float x, float y) { position_.set_x(x); position_.set_y(y); }

	//Rotation
	gef::Vector4 GetRotation() { return rotation_; }
	void SetRotations(gef::Vector4 rotation) { rotation_ = rotation; }

	//Scale
	gef::Vector4 GetScale() { return scale_; }
	void SetScale(gef::Vector4 scale) { scale_ = scale; }

	//Transform
	gef::Matrix44 GetTransform() { return transform_matrix_; }

	//Rotation Utilities
	void SetRotationX(float angle) { rotation_.set_x(angle); }
	void SetRotationY(float angle) { rotation_.set_y(angle); }
	void SetRotationZ(float angle) { rotation_.set_z(angle); }
protected:
	// Vectors and Matrices for world orientation
	gef::Vector4 position_, rotation_, scale_;

#pragma region Matrices
	gef::Matrix44 translation_matrix_;

	gef::Matrix44 rotation_matrix_x_,//
				  rotation_matrix_y_,// Handle each rotation axis seperately
				  rotation_matrix_z_;//

	gef::Matrix44 scale_matrix_;

	gef::Matrix44 transform_matrix_;
#pragma endregion 
};

