#pragma once

#include <vector>
#include <graphics\sprite.h>
#include <graphics/image_data.h>
#include <graphics/sprite.h>
#include <graphics/texture.h>

#include <Control.h>
#include <Entity.h>

class SpriteGrid :
	public Control
{
public:
	SpriteGrid(SceneApp & target, OnActivate function, gef::Sprite * img, Entity& entity);
	~SpriteGrid();

	void Update(float gameTime);
	void Reset();
	void Draw(gef::SpriteRenderer* spriteRenderer);

protected:
	std::vector<gef::Sprite*> sprite_;
	int _count = 0, _limit;
	Entity& _entity;
};

