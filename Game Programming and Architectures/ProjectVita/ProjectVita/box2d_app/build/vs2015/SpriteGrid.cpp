#include "SpriteGrid.h"

SpriteGrid::SpriteGrid(SceneApp& target, OnActivate function, gef::Sprite* img, Entity& entity)
	: Control(target, function, NULL)
	, _entity(entity)
{
	_count = entity.GetHealth();
	gef::Vector4 v;
	for (int i = 0; i < _count; i++)
	{
		v = _position;
		v += gef::Vector4(i * img->width(), 0, 0);
		img->set_position(v);
		sprite_.push_back(img);
	}
}

SpriteGrid::~SpriteGrid()
{
}

void SpriteGrid::Update(float gameTime)
{
}

void SpriteGrid::Reset()
{

}

void SpriteGrid::Draw(gef::SpriteRenderer* spriteRenderer)
{
	for (int i = 0; i < _entity.GetHealth(); i++)
	{
		spriteRenderer->DrawSprite(*sprite_[i]);
	}
}
