#include "Button.h"

Button::Button(gef::Sprite sprite, std::string text, gef::Vector4 position, gef::Vector4 size, gef::Font * font)
	: UIControl::UIControl(text, position, size, font)
{
	_sprite = sprite;
	_sprite.set_position(_position);
}

void Button::HandleInput(gef::InputManager * inputManager)
{
	gef::Keyboard* kb = inputManager->keyboard();
	if (kb->IsKeyPressed(gef::Keyboard::KC_RETURN))
		OnSelect();
}

void Button::Draw(gef::SpriteRenderer * spriteRenderer)
{
	UIControl::Draw(spriteRenderer);
	spriteRenderer->DrawSprite(_sprite);	
}

void Button::OnSelect()
{
	
}

Button::~Button()
{
}
