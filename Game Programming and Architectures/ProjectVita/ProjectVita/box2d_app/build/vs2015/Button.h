#pragma once

#include <graphics\sprite.h>
#include <graphics\image_data.h>
#include <graphics\texture.h>
#include <Control.h>

class Button :
	public Control
{
public:
	Button(SceneApp & target, OnActivate function, gef::Font * font, gef::Sprite sprite);
	void Draw(gef::SpriteRenderer* spriteRenderer);
	~Button();
protected:
	gef::Sprite _sprite;
};

