#include <Control.h>

Control::Control(SceneApp & target, OnActivate function, gef::Font * font)
	: _target(target)
	, _function(function)
	, _font(font)
{
	_position = gef::Vector4(0, 0, 0);
	_size = gef::Vector4(1, 0, 0);
	_colour.SetFromRGBA(0xffffffff);
	_selectedColour.SetFromRGBA(0xff0000ff);
}

Control::~Control()
{
}

void Control::Update(float deltaTime)
{
}

void Control::Draw(gef::SpriteRenderer * spriteRenderer)
{
	if(_hasFocus)
		_font->RenderText(spriteRenderer, _position - gef::Vector4(0, 16, 0), 1.0f, _selectedColour.GetRGBA(), gef::TJ_CENTRE, _text.c_str());
	else
		_font->RenderText(spriteRenderer, _position - gef::Vector4(0,16,0), 1.0f, _colour.GetRGBA(), gef::TJ_CENTRE, _text.c_str());
}

void Control::HandleInput(gef::InputManager * inputManager)
{
	if (inputManager->keyboard()->IsKeyPressed(gef::Keyboard::KC_RETURN))
		if(_function)
			Execute();
}

void Control::OnSelect()
{

}

void Control::Execute()
{
	(_target.*_function)();
}
