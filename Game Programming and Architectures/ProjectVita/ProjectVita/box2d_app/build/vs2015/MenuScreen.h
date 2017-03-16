#pragma once

#include <graphics\sprite.h>
#include <GameState.h>

class MenuScreen 
	: public GameState
{
public:
	MenuScreen(SceneApp& scene, gef::Font * font);
	~MenuScreen();
	void Initialize();
	void Update(float gameTime);
	void Draw();
	void CleanUp();
protected:
	Button* start_game_;
	Button* quit_;
	gef::Sprite* space_background_ = new gef::Sprite();
	gef::Vector2 scroll_speed_ = gef::Vector2(0, 0.005f);
};

