#include "UIControl.h"



UIControl::UIControl()
{
}

UIControl::UIControl(std::string text, gef::Vector4 position, gef::Vector4 size, gef::Font* font)
{
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
	_font->RenderText(spriteRenderer, _position, 1.0f, _colour.GetABGR(), gef::TJ_CENTRE, "", _text);
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
