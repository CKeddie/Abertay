#pragma once

#include <vector>
#include "Control.h"

class ControlManager 
{
public:
	ControlManager(gef::Font* font);
	ControlManager(gef::Font* font, std::vector<Control*> controls);
	~ControlManager();
	virtual void Update(float gameTime, gef::InputManager* inputManager);
	virtual void Draw(gef::SpriteRenderer* spriteRenderer);
	virtual void NextControl();
	virtual void PreviousControl();
	virtual void AddControl(Control* control);
	virtual void RemoveControl(int index);

	void SetFont(gef::Font* font);
	gef::Font* GetFont() { return _font; }

protected:
	std::vector<Control*> _controls;
	gef::Font* _font;

	int _selectedControl = 0;
	bool _acceptInput = true;
};

