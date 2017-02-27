#pragma once

#include <string>
#include <maths/vector4.h>
#include <graphics\font.h>
#include <graphics\colour.h>
#include <input\input_manager.h>

/*
Serves as a base abstract class for constructing UI Controls
*/
class UIControl
{
public:
	UIControl();
	virtual void Update(float deltaTime);
	virtual void Draw(gef::SpriteRenderer* spriteRenderer);
	virtual void HandleInput(gef::InputManager* inputManager);
	virtual void OnSelect();
	~UIControl();
protected:
	std::string _name;
	std::string _text;
	gef::Vector4 _size;
	gef::Vector4 _position;
	
	bool _hasFocus;
	bool _enabled;
	bool _visible;
	bool _tabStop;

	gef::Font* _font;
	gef::Colour _colour;
};

