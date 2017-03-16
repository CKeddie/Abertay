#include "Button.h"

class gef::SpriteRenderer;

Button::Button(SceneApp & target, OnActivate function, gef::Font * font, gef::Sprite sprite) 
	: Control(target, function, font)
{
	_sprite = sprite;
}

void Button::Draw(gef::SpriteRenderer * spriteRenderer)
{
	_sprite.set_position(_position);
	Control::Draw(spriteRenderer);
	spriteRenderer->DrawSprite(_sprite);
}

Button::~Button()
{
}
