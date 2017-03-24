#pragma once

#include <ControlManager.h>
#include <Button.h>

class SceneApp;

class GameState
{
public:
	GameState(SceneApp& scene, gef::Font * font);
	~GameState();
	virtual void Initialize();
	virtual void Update(float gameTime);
	virtual void Draw();
	virtual void CleanUp();
protected:
	ControlManager* control_manager_;
	SceneApp& scene_;
};