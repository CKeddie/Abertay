#pragma once
#include "UIControl.h"
#include "graphics\sprite.h"
#include "graphics\image_data.h"
#include "graphics\texture.h"

class Button :
	public UIControl
{
public:
	Button(gef::Sprite sprite, std::string text, gef::Vector4 position, gef::Vector4 size, gef::Font* font);
	void HandleInput(gef::InputManager* inputManager);
	void Draw(gef::SpriteRenderer* spriteRenderer);
	void OnSelect();
	~Button();
protected:
	gef::Sprite _sprite;
};

