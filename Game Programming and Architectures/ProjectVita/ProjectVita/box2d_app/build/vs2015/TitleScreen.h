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
	Button* button_start_;
	//background?
	//
};

