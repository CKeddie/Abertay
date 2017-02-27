#pragma once

#include <vector>
#include "UIControl.h"

class ControlManager 
{
public:
	ControlManager(gef::Font* font);
	ControlManager(gef::Font* font, std::vector<UIControl> controls);
	~ControlManager();
	virtual void Update(float gameTime, gef::InputManager* inputManager);
	virtual void Draw(gef::SpriteRenderer* spriteRenderer);
	virtual void NextControl();
	virtual void PreviousControl();
	virtual void AddControl(UIControl control);
	virtual void RemoveControl(int index);

	void SetFont(gef::Font* font);

protected:
	std::vector<UIControl> _controls;
	gef::Font* _font;

	int _selectedControl = 0;
	bool _acceptInput = true;
};

