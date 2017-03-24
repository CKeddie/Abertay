#pragma once

#include <string>
#include <maths/vector4.h>
#include <graphics\font.h>
#include <graphics\colour.h>

#include <input\input_manager.h>
#include <input\keyboard.h>

#include <graphics\sprite_renderer.h>

class SceneApp;

class Control
{
public:
	typedef void ( SceneApp::*OnActivate )(  );
	Control(SceneApp& target, OnActivate function, gef::Font* font);
	~Control();

	virtual void Update(float deltaTime);
	virtual void Draw(gef::SpriteRenderer* spriteRenderer);
	virtual void HandleInput(gef::InputManager* inputManager);
	virtual void OnSelect();
	
	void Execute();
	
	//Getters
	std::string Name() { return _name; }
	std::string Text() { return _text; }
	gef::Vector4 Size() { return _size; }
	gef::Vector4 Position() { return _position; }
	bool Focus() { return _hasFocus; }
	bool Enabled() { return _enabled; }
	bool Visible() { return _visible; }
	bool TabStop() { return _tabStop; }
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
	gef::Font* _font;
	gef::Colour _colour, _selectedColour;
private:
	SceneApp& _target;
	OnActivate _function;
};