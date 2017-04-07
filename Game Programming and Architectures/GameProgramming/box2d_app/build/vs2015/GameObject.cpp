#include "GameObject.h"



GameObject::GameObject() 
	: tranform_(NULL)
{
	tranform_ = new Transform();
	tranform_->UpdateMatrices();
}

GameObject::~GameObject()
{

}

void GameObject::Update(float gameTime)
{
	if(tranform_)
		tranform_->UpdateMatrices();
}

void GameObject::Render(gef::Renderer3D *)
{
	return;
}