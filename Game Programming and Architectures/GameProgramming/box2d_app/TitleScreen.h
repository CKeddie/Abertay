#pragma once

#include <GameState.h>

class TitleScreen 
	: public GameState
{
public:
	TitleScreen(SceneApp& scene, gef::Font* font);
	~TitleScreen();
	void Initialize();
	void Update(float gameTime);
	void Draw();
	void CleanUp();
protected:
	float deg = 0;
	Button* button_start_;
	gef::Sprite* warp_background_;
	gef::Sprite* title_sprite_;
	gef::Sprite* space_background_;
};

