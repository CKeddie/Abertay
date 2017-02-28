#pragma once

#include <string>
#include <maths/vector4.h>
#include <graphics\font.h>
#include <graphics\colour.h>
#include <graphics\sprite_renderer.h>

#include <input\input_manager.h>
#include <input\keyboard.h>

/*
Serves as a base abstract class for constructing UI Controls
*/
class UIControl
{
public:
	UIControl();
	UIControl(std::string text, gef::Vector4 position, gef::Vector4 size, gef::Font * font);
	virtual void Update(float deltaTime);
	virtual void Draw(gef::SpriteRenderer* spriteRenderer);
	virtual void HandleInput(gef::InputManager* inputManager);
	virtual void OnSelect();
	~UIControl();

	//__event void OnSelect();

	//Getters
	std::string Name() { return _name; }
	std::string Text() { return _text; }
	gef::Vector4 Size() { return _size; }
	gef::Vector4 Position() { return _position; }
	bool Focus() { return _hasFocus; }
	bool Enabled() { return _enabled; }
	bool Visible() { return _visible; }
	bool TabStop() { return _tabStop; }
	bool Trigger() { return _trigger; }
	gef::Font* Font() { return _font; }
	gef::Colour Colour() { return _colour; }

	//Setters
	void Name(std::string name) { _name = name; }
	void Text(std::string text) { _text = text; }
	void Size(gef::Vector4 size) { _size = size; }
	void Position(gef::Vector4 position) { _position = position; }
	void SetFocus(bool focus) { _hasFocus = focus; }
	void SetEnabled(bool enabled) { _enabled = enabled; }
	void SetVisible(bool visible) { _visible = visible; }
	void SetTabStop(bool tabStop) { _tabStop = tabStop; }
	void SetTrigger(bool trigger) { _trigger = trigger; }
	void SetFont(gef::Font* font) { _font = font; }
	void SetColour(gef::Colour colour) { _colour = colour; }
protected:
	std::string _name;
	std::string _text;
	gef::Vector4 _size;
	gef::Vector4 _position;
	bool _hasFocus;
	bool _enabled;
	bool _visible;
	bool _tabStop;
	bool _trigger;
	gef::Font* _font;
	gef::Colour _colour;
};

