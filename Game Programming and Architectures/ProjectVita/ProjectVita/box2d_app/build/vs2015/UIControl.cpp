#include "UIControl.h"



UIControl::UIControl()
{
}

UIControl::UIControl(std::string text, gef::Vector4 position, gef::Vector4 size, gef::Font* font)
{
	_colour.SetFromAGBR(0xffffffff);
	_text = text;
	_position = position;
	_size = size;
	_font = font;
}

void UIControl::Update(float deltaTime)
{
}

void UIControl::Draw(gef::SpriteRenderer * spriteRenderer)
{
	_font->RenderText(spriteRenderer, _position, 1.0f, _colour.GetABGR(), gef::TJ_CENTRE, _text.c_str(), _text);
}

void UIControl::HandleInput(gef::InputManager * inputManager)
{
}


void UIControl::OnSelect()
{
}

UIControl::~UIControl()
{
}
