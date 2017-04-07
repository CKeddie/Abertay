#pragma once
class Component
{
public:
	Component();
	virtual void Initialize();
	~Component();
protected:
	bool is_initialized_ = false;
};

