#pragma once
#include "Component.h"
class BoxCollider :
	public Component
{
public:
	
	BoxCollider(GameObject & parent);
	~BoxCollider();
};

